create table vehicle
(
    id       serial             not null
        constraint vehicle_pk
            primary key,
    type     varchar(64)        not null,
    capacity integer            not null
);

alter table vehicle
    owner to "user";

INSERT INTO public.vehicle (id, type, capacity) VALUES (1, 'bus', 70);
INSERT INTO public.vehicle (id, type, capacity) VALUES (2, 'bus', 70);
INSERT INTO public.vehicle (id, type, capacity) VALUES (3, 'bus', 70);
INSERT INTO public.vehicle (id, type, capacity) VALUES (4, 'bus', 65);
INSERT INTO public.vehicle (id, type, capacity) VALUES (5, 'bus', 65);
INSERT INTO public.vehicle (id, type, capacity) VALUES (6, 'bus', 65);
INSERT INTO public.vehicle (id, type, capacity) VALUES (7, 'bus', 75);
INSERT INTO public.vehicle (id, type, capacity) VALUES (8, 'bus', 75);
INSERT INTO public.vehicle (id, type, capacity) VALUES (9, 'bus', 75);
INSERT INTO public.vehicle (id, type, capacity) VALUES (10, 'bus', 75);
INSERT INTO public.vehicle (id, type, capacity) VALUES (11, 'bus', 75);
INSERT INTO public.vehicle (id, type, capacity) VALUES (12, 'bus', 75);
INSERT INTO public.vehicle (id, type, capacity) VALUES (13, 'bus', 75);
INSERT INTO public.vehicle (id, type, capacity) VALUES (14, 'bus', 75);
INSERT INTO public.vehicle (id, type, capacity) VALUES (15, 'bus', 75);
