create table vehicle_maintenance
(
    id          serial
        constraint vehicle_maintenance_pk
            primary key,
    vehicle_id  integer                                not null
        constraint vehicle_maintenance_vehicle_id_fk
            references vehicle
            on update cascade,
    description text                                   not null,
    time        timestamp with time zone default now() not null,
    cost_total  numeric(8, 2)                          not null
);

alter table vehicle_maintenance
    owner to "user";

INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (7, 'Oil Change', '2023-10-21 08:00:00+00', 50.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (5, 'Brake Inspection', '2023-10-21 09:00:00+00', 75.50);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (3, 'Tire Rotation', '2023-10-21 10:00:00+00', 40.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (4, 'Engine Tune-up', '2023-10-21 11:00:00+00', 120.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (6, 'Transmission Service', '2023-10-21 12:00:00+00', 90.25);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (2, 'Wheel Alignment', '2023-10-21 13:00:00+00', 65.75);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (8, 'A/C Recharge', '2023-10-21 14:00:00+00', 55.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (1, 'Battery Replacement', '2023-10-21 15:00:00+00', 80.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (11, 'Brake Pad Replacement', '2023-10-21 16:00:00+00', 95.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (9, 'Suspension Repair', '2023-10-21 17:00:00+00', 110.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (10, 'Coolant Flush', '2023-10-21 18:00:00+00', 70.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (12, 'Exhaust System Repair', '2023-10-21 19:00:00+00', 105.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (14, 'Spark Plug Replacement', '2023-10-21 20:00:00+00', 45.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (13, 'Fuel System Cleaning', '2023-10-21 21:00:00+00', 85.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (15, 'Windshield Wiper Replacement', '2023-10-21 22:00:00+00', 25.00);

