create table route_stop
(
    id       serial not null
        constraint table_name_pk
            primary key,
    route_id integer                                                not null
        constraint table_name_route_id_fk
            references route
            on update cascade on delete cascade,
    stop_id  integer                                                not null
        constraint table_name_stop_id_fk
            references stop
            on update cascade on delete cascade,
    ord_index integer not null,
    unique (route_id, ord_index),
    unique (route_id, stop_id)
);

alter table route_stop
    owner to "user";

INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (7, 10, 1);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (5, 8, 1);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (3, 6, 1);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (4, 9, 1);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (6, 11, 1);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (2, 7, 1);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (8, 12, 1);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (1, 5, 1);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (10, 13, 1);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (7, 15, 2);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (10, 14, 2);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (10, 15, 3);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (7, 6, 3);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (2, 9, 2);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (5, 10, 2);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (9, 4, 1);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (3, 12, 2);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (8, 14, 2);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (6, 5, 2);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (1, 15, 2);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (4, 7, 2);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (2, 13, 3);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (5, 9, 3);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (10, 8, 4);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (3, 11, 3);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (8, 6, 3);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (1, 7, 3);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (9, 10, 2);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (6, 14, 3);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (4, 15, 3);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (7, 3, 4);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (5, 11, 4);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (10, 4, 5);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (2, 8, 4);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (8, 15, 4);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (1, 6, 4);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (9, 7, 3);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (3, 9, 4);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (6, 10, 4);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (4, 13, 4);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (7, 8, 5);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (10, 12, 6);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (2, 5, 5);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (5, 14, 5);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (8, 2, 5);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (6, 3, 5);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (4, 11, 5);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (7, 4, 6);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (10, 9, 7);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (3, 13, 5);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (8, 7, 6);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (1, 13, 5);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (9, 15, 4);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (2, 14, 6);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (5, 7, 6);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (4, 10, 6);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (8, 8, 7);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (6, 6, 6);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (1, 3, 6);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (2, 2, 7);
