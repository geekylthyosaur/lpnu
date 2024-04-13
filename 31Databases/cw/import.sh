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
podman run --name database --env POSTGRES_USER=root --env POSTGRES_PASSWORD=password --publish 5432:5432 --volume ~/Downloads/melbourne.zip:/melbourne.zip:Z --detach database
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
podman exec -it database /tmp/venv/bin/python -c "
import csv
from faker import Faker
fake = Faker()
with open('/tmp/melbourne/drivers.csv', 'w', newline='') as f:
  writer = csv.writer(f, delimiter='|')
  writer.writerows([[fake.name()] for _ in range(2000)])
"
podman exec -it database /tmp/venv/bin/python -c "
import csv
from faker import Faker
import random
fake = Faker()
ticket_discounts = ['student', 'elder', 'veteran', None, None, None, None, None, None, None]
def ticket():
  discount = random.choice(ticket_discounts)
  balance = round(random.uniform(0, 100), 2)
  return [discount, balance]
with open('/tmp/melbourne/tickets.csv', 'w', newline='') as f:
  writer = csv.writer(f, delimiter='|')
  writer.writerows([ticket() for _ in range(1000)])
"
podman exec -it database psql -U root -d postgres -c 'create database src;'
podman exec -it database psql -U root -d src -c 'create extension if not exists "uuid-ossp";'
podman exec -it database psql -U root -d src -c "
create table public.route (
  id integer primary key not null,
  name character varying(64),
  full_name character varying(128)
);
alter table public.route owner to root;
"
podman exec -it database psql -U root -d src -c "copy public.route(id, name, full_name) from '/tmp/melbourne/routes.csv' delimiter '|' csv;"
podman exec -it database psql -U root -d src -c "create index idx_route on public.route(id);"
podman exec -it database psql -U root -d src -c "
create table public.stop (
  id integer primary key not null,
  name character varying(128),
  lat numeric(16,14),
  lon numeric(16,13)
);
alter table public.stop owner to root;
"
podman exec -it database psql -U root -d src -c "copy public.stop(id, name, lat, lon) from '/tmp/melbourne/stops.csv' delimiter '|' csv;"
podman exec -it database psql -U root -d src -c "create index idx_stop on public.stop(id);"
podman exec -it database psql -U root -d src -c "
create table public.route_stops (
  route_id integer references public.route(id),
  stop_id integer references public.stop(id),
  ord_idx integer not null,
  primary key (route_id, stop_id)
);
alter table public.route_stops owner to root;
"
podman exec -it database psql -U root -d src -c "copy public.route_stops(route_id, stop_id, ord_idx) from '/tmp/melbourne/route_stops.csv' delimiter '|' csv;"
podman exec -it database psql -U root -d src -c "create index idx_route_stops on public.route_stops(route_id, stop_id);"
podman exec -it database psql -U root -d src -c "
create table public.schedule (
  id serial not null,
  route_id integer references public.route(id),
  stop_id integer references public.stop(id),
  arr_time_ds integer,
  dep_time_ds integer,
  primary key (id)
);
alter table public.schedule owner to root;
"
podman exec -it database psql -U root -d src -c "copy public.schedule(route_id, stop_id, arr_time_ds, dep_time_ds) from '/tmp/melbourne/schedule.csv' delimiter '|' csv;"
podman exec -it database psql -U root -d src -c "
alter table public.schedule
  add column arr time,
  add column dep time;
"
podman exec -it database psql -U root -d src -c "
update public.schedule
  set arr = to_char((arr_time_ds % 86400 || ' second')::interval, 'HH24:MI:SS')::time,
    dep = to_char((dep_time_ds % 86400 || ' second')::interval, 'HH24:MI:SS')::time;
"
podman exec -it database psql -U root -d src -c "
alter table public.schedule
  drop column arr_time_ds,
  drop column dep_time_ds;
"
podman exec -it database psql -U root -d src -c "create index idx_route_stop on public.schedule (route_id, stop_id);"
podman exec -it database psql -U root -d src -c "
create table public.vehicle (
  license character varying(16) not null,
  capacity integer not null,
  route_id integer references public.route(id),
  primary key(license)
);
alter table public.vehicle owner to root;
"
podman exec -it database psql -U root -d src -c "copy public.vehicle(license, capacity) from '/tmp/melbourne/vehicles.csv' delimiter '|' csv;"
podman exec -it database psql -U root -d src -c "create index idx_vehicle on vehicle(license);"
podman exec -it database psql -U root -d src -c "
update vehicle as v
set route_id = subquery.route_id
from (
  select r.id as route_id, v.license, row_number() over (partition by v.license order by random()) as row_num
  from vehicle v
  join route r on true
) as subquery
where v.license = subquery.license and row_num = 1;
"
podman exec -it database psql -U root -d src -c "
create type ticket_discount as enum ('student', 'elder', 'veteran');
create table public.ticket (
  id uuid default uuid_generate_v4() not null,
  discount ticket_discount,
  balance numeric(8, 2) default 0 not null,
  primary key (id)
);
alter table public.ticket owner to root;
"
podman exec -it database psql -U root -d src -c "copy public.ticket(discount, balance) from '/tmp/melbourne/tickets.csv' delimiter '|' csv;"
podman exec -it database psql -U root -d src -c "
create table public.ticket_discount_mult (
  discount ticket_discount not null,
  mult numeric(2, 2) not null,
  primary key (discount)
);
insert into public.ticket_discount_mult(discount, mult)
values ('student', 0.5);
insert into public.ticket_discount_mult(discount, mult)
values ('elder', 0.3);
insert into public.ticket_discount_mult(discount, mult)
values ('veteran', 0.2);
"
podman exec -it database psql -U root -d src -c "
create table public.transaction (
  id uuid default uuid_generate_v4() not null,
  ticket_id uuid not null references public.ticket(id),
  route_id integer not null references public.route(id),
  vehicle_id character varying(16) not null references public.vehicle(license),
  from_stop_id integer not null references public.stop(id),
  to_stop_id integer not null references public.stop(id),
  fare numeric(8,2) not null,
  timestamp timestamp not null default now(),
  primary key(id)
);
alter table public.transaction owner to root;
"
podman exec -it database psql -U root -d src -c "
do \$\$
declare
  i integer := 0;
begin
  -- TODO while i < 1000 loop
  while i < 10 loop
    insert into public.transaction(route_id, ticket_id, vehicle_id, from_stop_id, to_stop_id, fare, timestamp)
    with stop_ids_cte as (
      select r.id as r_id,
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
      where (select 1 from vehicle v where v.route_id = r.id limit 1) = 1
      group by r.id
    )
    select
      r_id,
      (select t.id from ticket t order by (random() + stop_ids_cte.r_id*0) limit 1),
      (select v.license from vehicle v where v.route_id = r_id limit 1) as vehicle_id,
      stop_ids[1],
      stop_ids[2],
      (select floor((random() + stop_ids_cte.r_id*0) * (30 - 5 + 1) + 5)) as fare,
      (select current_date + arr from schedule where route_id = r_id and stop_id = stop_ids[2] order by random() limit 1) as timestamp
    from stop_ids_cte
    order by random()
    limit 100;
    i := i + 1;
  end loop;
end \$\$;
"
podman exec -it database psql -U root -d src -c "
create table public.driver (
  id serial not null,
  name character varying(64) not null,
  vehicle_id character varying(16) references public.vehicle(license),
  primary key(id)
);
alter table public.driver owner to root;
"
podman exec -it database psql -U root -d src -c "copy public.driver(name) from '/tmp/melbourne/drivers.csv' delimiter '|' csv;"
podman exec -it database psql -U root -d src -c "
update public.driver
set vehicle_id = vehicles.license
  from (
    select id, row_number() over (order by id) as row_num
    from public.driver
  ) as drivers
  inner join (
    select license, row_number() over (order by license) as row_num
    from public.vehicle
  ) as vehicles
  on drivers.row_num = vehicles.row_num
  where drivers.id = public.driver.id
  and drivers.row_num <= 1500;
"
podman exec -it database psql -U root -d src -c "
create table public.maintenance (
  id serial not null,
  vehicle_id character varying(16) not null references public.vehicle(license),
  driver_id integer not null references public.driver(id),
  description text not null,
  time timestamp default now() not null,
  cost numeric(8, 2) not null,
  primary key(id)
);
alter table public.maintenance owner to root;
"
podman exec -it database psql -U root -d src -c "
do \$\$
declare
  i integer := 0;
begin
  -- TODO while i < 1000 loop
  while i < 10 loop
    insert into public.maintenance(vehicle_id, driver_id, description, time, cost)
    select
      vehicle_id,
      id as driver_id,
      (select case
        when random() + id*0 < 0.2 then 'regular check-up'
        when random() + id*0 < 0.4 then 'oil change'
        when random() + id*0 < 0.6 then 'brake inspection'
        when random() + id*0 < 0.8 then 'tire rotation'
        else 'visit to gas station'
      end) as description,
      now() - '1 year'::interval * random() * 10 as time,
      (select floor((random() + id*0) * (30 - 5 + 1) + 5))*4 as cost
    from driver
    where vehicle_id is not null
    order by random()
    limit 100;
    i := i + 1;
  end loop;
end \$\$;
"
podman exec -it database psql -U root -d src -c "
create view public.routes_with_stops as
select
  s1.id as from_stop_id,
  s1.name as from_stop_name,
  s2.id as to_stop_id,
  s2.name as to_stop_name,
  r.id as route_id,
  (case when r.name is null then r.full_name else r.name end) as route_name
from stop s1
cross join stop s2
join route_stops rs1 on rs1.stop_id = s1.id
join route_stops rs2 on rs2.stop_id = s2.id
join route r on rs1.route_id = rs2.route_id and rs1.route_id = r.id
where s1.id <> s2.id;
alter view public.routes_with_stops owner to root;
"
podman exec -it database psql -U root -d src -c "
create view arrival_with_stops_in as
select from_stop_id, from_stop_name, to_stop_id, to_stop_name, route_id, route_name, to_char(arr_in, 'MI:SS') as arr_in from (
select
  s.from_stop_id,
  s.from_stop_name,
  s.to_stop_id,
  s.to_stop_name,
  s.route_id,
  (case when r.name is null then r.full_name else r.name end) as route_name,
  sch.arr - now()::time as arr_in
from routes_with_stops s
join schedule sch on s.route_id = sch.route_id and (s.from_stop_id = sch.stop_id or s.to_stop_id = sch.stop_id)
join route r on r.id = s.route_id) as arrival
where arr_in > interval '0 seconds' and arr_in < interval '1 hour'
order by arr_in;
alter view public.arrival_with_stops_in owner to root;
"
podman exec -it database psql -U root -d src -c "
create or replace function new_transaction(ticket_id uuid, vehicle_id character varying(16), from_stop_id integer, to_stop_id integer)
returns void as
\$\$
declare
  fare integer;
  r_id integer = (select route_id from vehicle v where v.license = vehicle_id);
begin
  if r_id is null then return; end if;

  fare = abs((select ord_idx from route_stops rs
  where rs.route_id = r_id and rs.stop_id = to_stop_id)
  - (select ord_idx from route_stops rs
  where rs.route_id = r_id and rs.stop_id = from_stop_id)) * 5 * coalesce((select mult from ticket_discount_mult d where d.discount = (select discount from ticket t where t.id = ticket_id)), 1);

  if fare is null then raise 'invalid vehicle_id for given stops'; end if;

  if (select balance from ticket t where t.id = ticket_id) - fare < 0 then raise 'not enough balance'; end if;

  update ticket t set balance = balance - fare where t.id = ticket_id;

  insert into transaction(ticket_id, route_id, vehicle_id, from_stop_id, to_stop_id, fare, timestamp)
  values (ticket_id, r_id, vehicle_id, from_stop_id, to_stop_id, fare, now());
end;
\$\$
language plpgsql;
"
podman exec -it database psql -U root -d src -c "
create or replace function next_stop(vehicle_id varchar, stop_id integer)
returns table (next_stop_id integer, stop_name varchar, arr_in text) as \$\$
begin
  return query
  select rs.stop_id, s.name as stop_name, to_char(((select sch.arr from schedule sch where s.id = sch.stop_id and rs.route_id = sch.route_id and sch.arr - now()::time > interval '0 seconds' limit 1) - now()::time), 'MI:SS') as arr_in
  from public.route_stops rs
  join public.stop s on rs.stop_id = s.id
  where rs.route_id = (select route_id from public.vehicle where license = vehicle_id)
  and rs.ord_idx > (
    select ord_idx from public.route_stops rs where route_id = (select route_id from public.vehicle where license = vehicle_id) and rs.stop_id = next_stop.stop_id
  )
  order by rs.ord_idx
  limit 1;
end;
\$\$ language plpgsql;
"
podman exec -it database psql -U root -d src -c "
create or replace function search_stop(s varchar)
returns table (
  id integer,
  name varchar,
  lat numeric,
  lon numeric
)
language plpgsql
as \$\$
begin
  return query execute '
    select id, name, lat, lon from public.stop
    where name ilike \$1
    limit 10;
  ' using '%' || s || '%';
end;
\$\$;
"
podman exec -it database psql -U root -d src -c "
create or replace function search_route(s varchar)
returns table (
  id integer,
  route_name varchar
)
language plpgsql
as \$\$
begin
  return query execute '
    select id, (case when name is null then full_name else name end) as route_name
    from public.route
    where name ilike \$1 or full_name ilike \$1
    limit 10;
  ' using '%' || s || '%';
end;
\$\$;
"
podman exec -it database psql -U root -d src -c "
create role manager;
create role driver;
create role passenger;
"
podman exec -it database psql -U root -d src -c "
grant select on public.routes_with_stops to passenger;
grant select on public.arrival_with_stops_in to passenger;
grant select on public.vehicle to passenger;
grant select on public.route_stops to passenger;
grant select on public.stop to passenger;
grant select on public.route to passenger;
grant select on public.ticket to passenger;
grant update on public.ticket to passenger;
grant select on public.ticket_discount_mult to passenger;
grant execute on function new_transaction(uuid, character varying(16), integer, integer) to passenger;
grant execute on function search_stop(varchar) to passenger;
grant execute on function search_route(varchar) to passenger;

grant select on public.vehicle to driver;
grant select on public.route_stops to driver;
grant select on public.schedule to driver;
grant select on public.stop to driver;
grant execute on function next_stop(character varying(16), integer) to driver;
grant insert on public.maintenance to driver;
grant usage, select on sequence maintenance_id_seq to driver;

grant select on all tables in schema public to manager;
grant insert on all tables in schema public to manager;
grant update on all tables in schema public to manager;
grant execute on all functions in schema public to manager;
"
