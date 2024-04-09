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
    license_plate = fake.license_plate()
    capacity = random.randint(10, 15) * 10
    return [license, capacity]
with open('/tmp/melbourne/vehicles.csv', 'w', newline='') as f:
    writer = csv.writer(f, delimiter='|')
    writer.writerows([vehicle() for _ in range(1500)])
"
podman exec -it database psql -U user -d postgres -c 'create database src;'
podman exec -it database psql -U user -d postgres -c 'create extension if not exists "uuid-ossp";'
podman exec -it database psql -U user -d src -c "
create table public.route (
  id integer primary key not null,
  name character varying(64),
  full_name character varying(128)
);
"
podman exec -it database psql -U user -d src -c "copy public.route(id, name, full_name) from '/tmp/melbourne/routes.csv' delimiter '|' csv;"
podman exec -it database psql -U user -d src -c "
create table public.stop (
  id integer primary key not null,
  name character varying(128),
  lat numeric(16,14),
  lon numeric(16,13)
);
"
podman exec -it database psql -U user -d src -c "copy public.stop(id, name, lat, lon) from '/tmp/melbourne/stops.csv' delimiter '|' csv;"
podman exec -it database psql -U user -d src -c "
create table public.route_stops (
  route_id integer references public.route(id),
  stop_id integer references public.stop(id),
  ord_idx integer not null,
  primary key (route_id, stop_id)
);
"
podman exec -it database psql -U user -d src -c "copy public.route_stops(route_id, stop_id, ord_idx) from '/tmp/melbourne/route_stops.csv' delimiter '|' csv;"
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
podman exec -it database psql -U user -d src -c "
create table public.vehicle (
  license character varying(16) not null,
  capacity integer not null,
  primary key(license)
);
"
podman exec -it database psql -U user -d src -c "copy public.vehicle(license, capacity) from '/tmp/melbourne/vehicles.csv' delimiter '|' csv;"
podman exec -it database psql -U user -d src -c "
create table public.transaction (
  id uuid default uuid_generate_v4(),
  route_id integer not null references public.route(id),
  vehicle_id character varying(16) not null references public.vehicle(license),
  from_stop_id interger not null references public.stop(id),
  to_stop_id interger not null references public.stop(id),
  fare numeric(8,2) not null,
  timestampt integer not null,
  primary key(id)
);
"
