create table route_vehicle
(
    id               serial
        constraint route_vehicle_pk
            primary key,
    route_id         integer not null
        constraint route_vehicle_route_id_fk
            references route
            on update cascade on delete cascade,
    last_lat         numeric(8, 6),
    last_lon         numeric(9, 6),
    last_coords_time timestamp with time zone,
    next_stop        integer
        constraint route_vehicle_stop_id_fk
            references stop
            on update cascade on delete cascade,
    vehicle_id       integer not null
        constraint route_vehicle_vahicle_id_fk
            references vehicle
            on update cascade on delete cascade
);

alter table route_vehicle
    owner to "user";

INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (7, 40.123456, -74.654321, '2023-10-21 08:30:00+00', 2, 11);
INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (5, 41.987654, -75.123456, '2023-10-21 09:15:00+00', NULL, 12);
INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (3, 39.567890, -73.987654, '2023-10-21 10:00:00+00', 4, 13);
INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (4, 40.765432, -74.234567, '2023-10-21 11:45:00+00', 5, 14);
INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (6, 41.234567, -75.345678, NULL, 3, 15);
INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (2, NULL, NULL, NULL, 2, 1);
INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (8, 40.345678, -74.567890, '2023-10-21 17:00:00+00', 1, 2);
INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (1, 41.654321, -75.678901, '2023-10-21 18:45:00+00', 7, 3);
INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (11, 39.432109, -73.789012, '2023-10-21 20:30:00+00', 8, 4);
INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (9, 40.789012, -74.890123, '2023-10-21 22:15:00+00', NULL, 5);
INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (10, 41.567890, -75.901234, NULL, 10, 6);
INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (12, 39.234567, -73.012345, '2023-10-22 08:30:00+00', 11, 7);
INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (14, 40.012345, -74.123456, '2023-10-22 09:15:00+00', 12, 8);
INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (13, 41.345678, -75.234567, '2023-10-22 10:00:00+00', 13, 9);
INSERT INTO route_vehicle (route_id, last_lat, last_lon, last_coords_time, next_stop, vehicle_id) VALUES (15, 39.789012, -73.345678, '2023-10-22 11:45:00+00', 14, 10);
