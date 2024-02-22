create table vehicle
(
    id       serial             not null
        constraint vehicle_pk
            primary key,
    type     varchar(64)        not null,
    license_plate varchar(64)   not null,
    capacity integer            not null
);

alter table vehicle
    owner to "user";

INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (1, 'bus', 'ABC123', 70);
INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (2, 'bus', 'XYZ456', 70);
INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (3, 'bus', 'DEF789', 70);
INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (4, 'bus', 'GHI101', 65);
INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (5, 'bus', 'JKL202', 65);
INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (6, 'bus', 'MNO303', 65);
INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (7, 'bus', 'PQR404', 75);
INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (8, 'bus', 'STU505', 75);
INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (9, 'bus', 'VWX606', 75);
INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (10, 'bus', 'YZA707', 75);
INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (11, 'bus', 'BCD808', 75);
INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (12, 'bus', 'EFG909', 75);
INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (13, 'bus', 'HIJ010', 75);
INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (14, 'bus', 'KLM111', 75);
INSERT INTO public.vehicle (id, type, license_plate, capacity) VALUES (15, 'bus', 'NOP212', 75);
