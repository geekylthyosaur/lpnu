create table ticket
(
    id             serial
        constraint ticket_pk
            primary key,
    transaction_id varchar(64)              not null,
    fare           numeric(8, 2)            not null,
    time           timestamp with time zone not null,
    route_id       integer                  not null
        constraint ticket_route_id_fk
            references route,
    vehicle_id     integer
        constraint ticket_vehicle_id_fk
            references vehicle
);

alter table ticket
    owner to "user";

INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('ABC123', 25.50, '2023-10-21 08:30:00+00', 7, 10);
INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('DEF456', 15.75, '2023-10-21 09:15:00+00', 3, 5);
INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('GHI789', 30.00, '2023-10-21 10:00:00+00', 6, 9);
INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('JKL012', 18.25, '2023-10-21 11:45:00+00', 2, 4);
INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('MNO345', 21.75, '2023-10-21 13:30:00+00', 8, 14);
INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('PQR678', 27.50, '2023-10-21 15:15:00+00', 1, 8);
INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('STU901', 14.00, '2023-10-21 17:00:00+00', 5, 13);
INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('VWX234', 35.75, '2023-10-21 18:45:00+00', 4, 7);
INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('YZA567', 20.50, '2023-10-21 20:30:00+00', 10, 1);
INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('BCD890', 22.25, '2023-10-21 22:15:00+00', 9, 6);
INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('EFG123', 19.75, '2023-10-22 08:30:00+00', 14, 11);
INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('HIJ456', 28.00, '2023-10-22 09:15:00+00', 11, 2);
INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('KLM789', 23.25, '2023-10-22 10:00:00+00', 12, 3);
INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('NOP012', 26.50, '2023-10-22 11:45:00+00', 15, 12);
INSERT INTO ticket (transaction_id, fare, time, route_id, vehicle_id) VALUES ('QRS345', 31.75, '2023-10-22 13:30:00+00', 13, 15);
