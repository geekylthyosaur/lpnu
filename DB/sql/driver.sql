create table driver
(
    id         serial
        constraint driver_pk
            primary key,
    first_name varchar(64)   not null,
    last_name  varchar(64)   not null,
    salary     numeric(8, 2) not null
);

alter table driver
    owner to "user";

INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (1, 'Jackson', 'Smith', 5000.00);
INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (2, 'Liam', 'Williams', 6500.00);
INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (3, 'Sophia', 'Turner', 6000.00);
INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (4, 'Olivia', 'Davis', 5800.00);
INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (5, 'Emily', 'Johnson', 6000.00);
INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (6, 'Ethan', 'Brown', 4800.00);
INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (7, 'Ava', 'Martinez', 5200.00);
INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (8, 'Mason', 'Johnson', 6000.00);
INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (9, 'Isabella', 'Anderson', 5500.00);
INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (10, 'Noah', 'Wilson', 6200.00);
INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (11, 'Oliver', 'Jones', 5800.00);
INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (12, 'Emma', 'Garcia', 5300.00);
INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (13, 'Lucas', 'Lee', 5700.00);
INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (14, 'Harper', 'Hernandez', 5900.00);
INSERT INTO public.driver (id, first_name, last_name, salary) VALUES (15, 'Logan', 'Davis', 5100.00);
