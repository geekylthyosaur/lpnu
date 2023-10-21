create table driver_route
(
    id         serial
        constraint driver_route_pk
            primary key,
    driver_id  integer not null
        constraint driver_route_driver_id_fk
            references driver
            on update cascade on delete cascade,
    vehicle_id integer not null
        constraint driver_route_vehicle_id_fk
            references vehicle
            on update cascade on delete cascade,
    route_id   integer not null
        constraint driver_route_route_id_fk
            references route
            on update cascade on delete cascade
);

alter table driver_route
    owner to "user";

INSERT INTO driver_route (driver_id, vehicle_id, route_id) VALUES (7, 10, 7);
INSERT INTO driver_route (driver_id, vehicle_id, route_id) VALUES (5, 8, 5);
INSERT INTO driver_route (driver_id, vehicle_id, route_id) VALUES (3, 6, 3);
INSERT INTO driver_route (driver_id, vehicle_id, route_id) VALUES (4, 9, 4);
INSERT INTO driver_route (driver_id, vehicle_id, route_id) VALUES (6, 11, 6);
INSERT INTO driver_route (driver_id, vehicle_id, route_id) VALUES (2, 7, 2);
INSERT INTO driver_route (driver_id, vehicle_id, route_id) VALUES (8, 12, 8);
INSERT INTO driver_route (driver_id, vehicle_id, route_id) VALUES (1, 5, 1);
INSERT INTO driver_route (driver_id, vehicle_id, route_id) VALUES (11, 13, 11);
INSERT INTO driver_route (driver_id, vehicle_id, route_id) VALUES (9, 15, 9);
INSERT INTO driver_route (driver_id, vehicle_id, route_id) VALUES (10, 14, 10);
INSERT INTO driver_route (driver_id, vehicle_id, route_id) VALUES (12, 15, 12);
