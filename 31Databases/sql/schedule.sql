create table schedule
(
    id             serial not null
        constraint timetable_pk
            primary key,
    vehicle_id     integer                                               not null
        constraint timetable_vehicle_id_fk
            references vehicle
            on update cascade on delete cascade,
    route_id       integer                                               not null
        constraint timetable_route_id_fk
            references route
            on update cascade on delete cascade,
    stop_id        integer                                               not null
        constraint timetable_stop_id_fk
            references stop
            on update cascade on delete cascade,
    departure_time timestamp with time zone                              not null,
    arrival_time   timestamp with time zone                              not null
);

alter table schedule
    owner to "user";

INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (7, 10, 7, '2023-10-21 08:00:00+00', '2023-10-21 08:30:00+00');
INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (5, 8, 5, '2023-10-21 09:00:00+00', '2023-10-21 09:30:00+00');
INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (3, 6, 3, '2023-10-21 10:00:00+00', '2023-10-21 10:30:00+00');
INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (4, 9, 4, '2023-10-21 11:00:00+00', '2023-10-21 11:30:00+00');
INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (6, 11, 6, '2023-10-21 12:00:00+00', '2023-10-21 12:30:00+00');
INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (2, 7, 2, '2023-10-21 13:00:00+00', '2023-10-21 13:30:00+00');
INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (8, 12, 8, '2023-10-21 14:00:00+00', '2023-10-21 14:30:00+00');
INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (1, 5, 1, '2023-10-21 15:00:00+00', '2023-10-21 15:30:00+00');
INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (11, 13, 11, '2023-10-21 16:00:00+00', '2023-10-21 16:30:00+00');
INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (9, 15, 9, '2023-10-21 17:00:00+00', '2023-10-21 17:30:00+00');
INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (10, 14, 10, '2023-10-21 18:00:00+00', '2023-10-21 18:30:00+00');
INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (12, 2, 9, '2023-10-21 19:00:00+00', '2023-10-21 19:30:00+00');
INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (14, 4, 14, '2023-10-21 20:00:00+00', '2023-10-21 20:30:00+00');
INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (13, 3, 13, '2023-10-21 21:00:00+00', '2023-10-21 21:30:00+00');
INSERT INTO schedule (vehicle_id, route_id, stop_id, arrival_time, departure_time) VALUES (15, 1, 12, '2023-10-21 22:00:00+00', '2023-10-21 22:30:00+00');

