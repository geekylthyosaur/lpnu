#!/bin/bash

set -xeu -o pipefail

podman stop database
podman rm database
podman run --name database --env POSTGRES_USER=user --env POSTGRES_PASSWORD=password --publish 5432:5432 --volume ~/Downloads/melbourne.zip:/melbourne.zip:Z --detach database
podman exec -it database /bin/bash -c 'unzip /melbourne.zip -d /tmp'
podman exec -it database /bin/bash -c 'python3 -m venv /tmp/venv'
podman exec -it database /bin/bash -c 'source /tmp/venv/bin/activate'
podman exec -it database /bin/bash -c '/tmp/venv/bin/pip install geojson-to-sqlite'
podman exec -it database /bin/bash -c '/tmp/venv/bin/geojson-to-sqlite /tmp/melbourne/route_stops.sqlite route_stops /tmp/melbourne/routes.geojson'
podman exec -it database /bin/bash -c 'sqlite3 /tmp/melbourne/route_stops.sqlite -json "select route_I, geometry from route_stops" > /tmp/melbourne/route_stops.json'
podman exec -it database /bin/bash -c 'sqlite3 /tmp/melbourne/week.sqlite "select route_I, name, long_name from routes where type = 3;" > /tmp/melbourne/routes.csv'
podman exec -it database /bin/bash -c 'sqlite3 /tmp/melbourne/week.sqlite "select stop_I, name, lat, lon from stops;" > /tmp/melbourne/stops.csv'
podman exec -it database psql -U user -d postgres -c 'create database src;'
podman exec -it database psql -U user -d src -c "
create table public.route (
  id integer primary key not null,
  name character varying(64),
  full_name character varying(128)
);
copy public.route(id, name, full_name) from '/tmp/melbourne/routes.csv' delimiter '|' csv header;
"
podman exec -it database psql -U user -d src -c "
create table public.stop (
  id integer primary key not null,
  name character varying(128),
  lat numeric(16,14),
  lon numeric(16,13)
);
copy public.stop(id, name, lat, lon) from '/tmp/melbourne/stops.csv' delimiter '|' csv header;
"
podman exec -it database psql -U user -d src -c '
create table public.route_stops (
    route_id integer references public.route(id),
    stop_id integer references public.stop(id),
    ord_idx integer not null,
    primary key (route_id, stop_id)
);
'
podman exec -it database psql -U user -d src -c "
create temporary table route_stops_coordinates (
    route_id integer,
    coordinates jsonb,
    primary key (route_id)
);
insert into route_stops_coordinates (route_id, coordinates)
select
    (json_data->>'route_I')::integer as route_id,
    ((json_data->>'geometry')::jsonb->>'coordinates')::jsonb as coordinates
from jsonb_array_elements(pg_read_file('/tmp/melbourne/route_stops.json')::jsonb) as json_build_array(json_data);
insert into public.route_stops (route_id, stop_id, ord_idx)
select 
    rsc.route_id,
    s.id,
    row_number() over (partition by rsc.route_id order by idx) as ord_idx
from 
    route_stops_coordinates rsc
    join public.route r on r.id = rsc.route_id
    cross join lateral jsonb_array_elements(rsc.coordinates) with ordinality as coord(lonlat, idx)
    join public.stop s on s.lat = (coord.lonlat->>1)::numeric and s.lon = (coord.lonlat->>0)::numeric
on conflict (route_id, stop_id) do nothing;
"
