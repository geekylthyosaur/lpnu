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

INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (7, 'Oil Change', '2023-10-21 08:45:00+00', 50.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (5, 'Brake Inspection', '2023-10-22 10:20:00+00', 75.50);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (3, 'Tire Rotation', '2023-10-23 12:15:00+00', 40.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (4, 'Engine Tune-up', '2023-10-24 14:30:00+00', 120.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (6, 'Transmission Service', '2023-10-25 16:50:00+00', 90.25);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (2, 'Wheel Alignment', '2023-10-26 18:25:00+00', 65.75);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (8, 'A/C Recharge', '2023-10-27 20:05:00+00', 55.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (1, 'Battery Replacement', '2023-10-28 09:40:00+00', 80.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (11, 'Brake Pad Replacement', '2023-10-29 11:55:00+00', 95.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (9, 'Suspension Repair', '2023-10-30 13:10:00+00', 110.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (10, 'Coolant Flush', '2023-10-31 15:40:00+00', 70.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (12, 'Exhaust System Repair', '2023-11-01 17:25:00+00', 105.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (14, 'Spark Plug Replacement', '2023-11-02 19:15:00+00', 45.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (13, 'Fuel System Cleaning', '2023-11-03 21:30:00+00', 85.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (15, 'Windshield Wiper Replacement', '2023-11-04 22:45:00+00', 25.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (7, 'Brake Pad Replacement', '2023-10-15 08:30:00+00', 90.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (5, 'Oil Change', '2023-10-16 14:15:00+00', 50.25);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (3, 'Tire Rotation', '2023-10-18 10:00:00+00', 40.50);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (4, 'Transmission Service', '2023-10-19 13:45:00+00', 110.75);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (6, 'Wheel Alignment', '2023-10-21 11:30:00+00', 60.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (2, 'Battery Replacement', '2023-10-22 09:15:00+00', 75.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (8, 'Engine Tune-up', '2023-10-25 17:20:00+00', 125.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (1, 'Suspension Repair', '2023-10-27 15:10:00+00', 95.50);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (11, 'Coolant Flush', '2023-10-28 14:40:00+00', 70.25);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (9, 'Exhaust System Repair', '2023-10-29 16:00:00+00', 105.50);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (12, 'Windshield Wiper Replacement', '2023-10-30 08:30:00+00', 35.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (14, 'Fuel System Cleaning', '2023-11-02 12:45:00+00', 85.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (13, 'Brake Inspection', '2023-11-03 15:20:00+00', 60.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (5, 'Oil Change', '2023-11-06 09:10:00+00', 55.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (7, 'Tire Rotation', '2023-11-07 13:30:00+00', 42.75);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (8, 'A/C Recharge', '2023-11-09 17:45:00+00', 70.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (9, 'Battery Replacement', '2023-11-10 08:20:00+00', 85.50);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (10, 'Suspension Repair', '2023-11-12 10:55:00+00', 115.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (11, 'Engine Tune-up', '2023-11-14 14:15:00+00', 120.00);
INSERT INTO vehicle_maintenance (vehicle_id, description, time, cost_total) VALUES (12, 'Coolant Flush', '2023-11-16 16:40:00+00', 72.50);

