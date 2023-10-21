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
    ord_index integer not null
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
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (7, 15, 3);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (10, 14, 2);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (10, 15, 3);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (7, 6, 2);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (2, 9, 2);
INSERT INTO route_stop (route_id, stop_id, ord_index) VALUES (5, 10, 2);
