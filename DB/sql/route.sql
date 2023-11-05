create table route
(
    id            serial
        constraint route_pk
            primary key,
    name          varchar(64) not null,
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

INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('Downtown Express', 3, 12);
INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('City Loop', 9, 7);
INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('Suburban Shuttle', 2, 8);
INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('Coastal Connection', 5, 11);
INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('Mountain Explorer', 6, 14);
INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('Airport Shuttle', 4, 10);
INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('Metro Line', 7, 13);
INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('City Center Route', 1, 9);
INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('Riverfront Express', 11, 15);
INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('Countryside Connector', 12, 6);
INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('Hillside Express', 8, 5);
INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('Ocean Breeze Line', 13, 3);
INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('Subway Route', 10, 4);
INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('Downtown Loop', 14, 2);
INSERT INTO route (name, first_stop_id, last_stop_id) VALUES ('Cityscape Tour', 15, 1);

