#!/bin/bash

set -xeu -o pipefail

podman stop --ignore database
podman rm --ignore database
if [ ! -f ~/Downloads/melbourne.zip ]; then
  curl -o ~/Downloads/melbourne.zip https://zenodo.org/records/1186215/files/melbourne.zip?download=1
fi
if ! podman image exists database &> /dev/null; then
  podman build -t database .
fi
podman run --name database --env POSTGRES_USER=user --env POSTGRES_PASSWORD=password --publish 5432:5432 --volume ~/Downloads/melbourne.zip:/melbourne.zip:Z --detach database
podman exec -it database /bin/bash -c 'unzip /melbourne.zip -d /tmp'
podman exec -it database /bin/bash -c 'python3 -m venv /tmp/venv'
podman exec -it database /bin/bash -c '/tmp/venv/bin/pip install faker'
podman exec -it database /bin/bash -c '
sqlite3 /tmp/melbourne/week.sqlite "
  select route_I, stop_I, row_number() over (partition by route_I order by stop_I) as ord_idx 
  from (select distinct t.route_I as route_I, stop_I
    from stop_times
    join main.trips t on stop_times.trip_I = t.trip_I
    join main.routes r on t.route_I = r.route_I and r.type = 3
    order by dep_time_ds and t.route_I
  );
" > /tmp/melbourne/route_stops.csv
'
podman exec -it database /bin/bash -c 'sqlite3 /tmp/melbourne/week.sqlite "select route_I, name, long_name from routes where type = 3;" > /tmp/melbourne/routes.csv'
podman exec -it database /bin/bash -c 'sqlite3 /tmp/melbourne/week.sqlite "select stop_I, name, lat, lon from stops;" > /tmp/melbourne/stops.csv'
podman exec -it database /bin/bash -c '
sqlite3 /tmp/melbourne/week.sqlite "
  select distinct t.route_I, stop_I, arr_time_ds, dep_time_ds
  from stop_times
  join main.trips t on stop_times.trip_I = t.trip_I
  join main.routes r on t.route_I = r.route_I and r.type = 3
  order by t.route_I, stop_I, dep_time_ds;
" > /tmp/melbourne/schedule.csv
'
podman exec -it database /tmp/venv/bin/python -c "
import csv
import random
from faker import Faker
fake = Faker()
def vehicle():
    license = fake.license_plate()[:16]
    capacity = random.randint(10, 15) * 10
    return [license, capacity]
with open('/tmp/melbourne/vehicles.csv', 'w', newline='') as f:
    writer = csv.writer(f, delimiter='|')
    writer.writerows([vehicle() for _ in range(1500)])
"
podman exec -it database psql -U user -d postgres -c 'create database src;'
podman exec -it database psql -U user -d src -c 'create extension if not exists "uuid-ossp";'
podman exec -it database psql -U user -d src -c "
create table public.route (
  id integer primary key not null,
  name character varying(64),
  full_name character varying(128)
);
"
podman exec -it database psql -U user -d src -c "copy public.route(id, name, full_name) from '/tmp/melbourne/routes.csv' delimiter '|' csv;"
podman exec -it database psql -U user -d src -c "create index idx_route on public.route(id);"
podman exec -it database psql -U user -d src -c "
create table public.stop (
  id integer primary key not null,
  name character varying(128),
  lat numeric(16,14),
  lon numeric(16,13)
);
"
podman exec -it database psql -U user -d src -c "copy public.stop(id, name, lat, lon) from '/tmp/melbourne/stops.csv' delimiter '|' csv;"
podman exec -it database psql -U user -d src -c "create index idx_stop on public.stop(id);"
podman exec -it database psql -U user -d src -c "
create table public.route_stops (
  route_id integer references public.route(id),
  stop_id integer references public.stop(id),
  ord_idx integer not null,
  primary key (route_id, stop_id)
);
"
podman exec -it database psql -U user -d src -c "copy public.route_stops(route_id, stop_id, ord_idx) from '/tmp/melbourne/route_stops.csv' delimiter '|' csv;"
podman exec -it database psql -U user -d src -c "create index idx_route_stops on public.route_stops(route_id, stop_id);"
podman exec -it database psql -U user -d src -c "
create table public.schedule (
  id serial not null,
  route_id integer references public.route(id),
  stop_id integer references public.stop(id),
  arr_time_ds integer,
  dep_time_ds integer,
  primary key (id)
);
"
podman exec -it database psql -U user -d src -c "copy public.schedule(route_id, stop_id, arr_time_ds, dep_time_ds) from '/tmp/melbourne/schedule.csv' delimiter '|' csv;"
podman exec -it database psql -U user -d src -c "
alter table public.schedule
  add column arr time,
  add column dep time;
"
podman exec -it database psql -U user -d src -c "
update public.schedule
  set arr = to_char((arr_time_ds % 86400 || ' second')::interval, 'HH24:MI:SS')::time,
    dep = to_char((dep_time_ds % 86400 || ' second')::interval, 'HH24:MI:SS')::time;
"
podman exec -it database psql -U user -d src -c "
alter table public.schedule
  drop column arr_time_ds,
  drop column dep_time_ds;
"
podman exec -it database psql -U user -d src -c "create index idx_route_stop on public.schedule (route_id, stop_id);"
podman exec -it database psql -U user -d src -c "
create table public.vehicle (
  license character varying(16) not null,
  capacity integer not null,
  primary key(license)
);
"
podman exec -it database psql -U user -d src -c "copy public.vehicle(license, capacity) from '/tmp/melbourne/vehicles.csv' delimiter '|' csv;"
podman exec -it database psql -U user -d src -c "create index idx_vehicle on vehicle(license);"
podman exec -it database psql -U user -d src -c "
create table public.transaction (
  id uuid default uuid_generate_v4(),
  route_id integer not null references public.route(id),
  vehicle_id character varying(16) not null references public.vehicle(license),
  from_stop_id integer not null references public.stop(id),
  to_stop_id integer not null references public.stop(id),
  fare numeric(8,2) not null,
  timestamp integer not null,
  primary key(id)
);
"
podman exec -it database psql -U user -d src -c "
do \$\$
declare
    i integer := 0;
begin
    while i < 1000 loop
    insert into public.transaction(route_id, vehicle_id, from_stop_id, to_stop_id, fare, timestamp)
    with stop_ids_cte as (
        select r.id as route_id,
               array_agg(s.id) as stop_ids
        from route r
        cross join lateral (
            select s.id
            from route_stops rs
            join stop s on rs.stop_id = s.id
            where rs.route_id = r.id
            order by random()
            limit 2
        ) s
        group by r.id
        order by random()
        limit 1
    )
    select
        route_id,
        (select v.license from vehicle v order by random() limit 1) as vehicle_id,
        stop_ids[1],
        stop_ids[2],
        (select floor(random() * (30 - 5 + 1) + 5)) as fare,
        extract (epoch from (select current_date + arr from schedule where route_id = route_id and stop_id = stop_ids[2] order by random() limit 1)) as timestamp
    from stop_ids_cte
    order by random()
    limit 1;
    i := i + 1;
    end loop;
end \$\$;
"
