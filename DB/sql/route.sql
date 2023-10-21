create table route
(
    id            serial
        constraint route_pk
            primary key,
    first_stop_id integer not null
        constraint route_stop_id_fk
            references stop
            on update cascade,
    last_stop_id  integer not null
        constraint route_stop_id_fk2
            references stop
            on update cascade
);

alter table route
    owner to "user";

INSERT INTO route (first_stop_id, last_stop_id) VALUES (3, 12);
INSERT INTO route (first_stop_id, last_stop_id) VALUES (9, 7);
INSERT INTO route (first_stop_id, last_stop_id) VALUES (2, 8);
INSERT INTO route (first_stop_id, last_stop_id) VALUES (5, 11);
INSERT INTO route (first_stop_id, last_stop_id) VALUES (6, 14);
INSERT INTO route (first_stop_id, last_stop_id) VALUES (4, 10);
INSERT INTO route (first_stop_id, last_stop_id) VALUES (7, 13);
INSERT INTO route (first_stop_id, last_stop_id) VALUES (1, 9);
INSERT INTO route (first_stop_id, last_stop_id) VALUES (11, 15);
INSERT INTO route (first_stop_id, last_stop_id) VALUES (12, 6);
INSERT INTO route (first_stop_id, last_stop_id) VALUES (8, 5);
INSERT INTO route (first_stop_id, last_stop_id) VALUES (13, 3);
INSERT INTO route (first_stop_id, last_stop_id) VALUES (10, 4);
INSERT INTO route (first_stop_id, last_stop_id) VALUES (14, 2);
INSERT INTO route (first_stop_id, last_stop_id) VALUES (15, 1);
