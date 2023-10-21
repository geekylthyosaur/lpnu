create table stop
(
    id   serial
        constraint stop_pk
            primary key,
    name varchar(64)   not null,
    lat  numeric(8, 6) not null,
    lon  numeric(9, 6) not null
);

alter table stop
    owner to "user";

INSERT INTO stop (name, lat, lon) VALUES ('Stop A', 40.123456, -74.654321);
INSERT INTO stop (name, lat, lon) VALUES ('Stop B', 41.987654, -75.123456);
INSERT INTO stop (name, lat, lon) VALUES ('Stop C', 39.567890, -73.987654);
INSERT INTO stop (name, lat, lon) VALUES ('Stop D', 40.765432, -74.234567);
INSERT INTO stop (name, lat, lon) VALUES ('Stop E', 41.234567, -75.345678);
INSERT INTO stop (name, lat, lon) VALUES ('Stop F', 39.876543, -73.456789);
INSERT INTO stop (name, lat, lon) VALUES ('Stop G', 40.345678, -74.567890);
INSERT INTO stop (name, lat, lon) VALUES ('Stop H', 41.654321, -75.678901);
INSERT INTO stop (name, lat, lon) VALUES ('Stop I', 39.432109, -73.789012);
INSERT INTO stop (name, lat, lon) VALUES ('Stop J', 40.789012, -74.890123);
INSERT INTO stop (name, lat, lon) VALUES ('Stop K', 41.567890, -75.901234);
INSERT INTO stop (name, lat, lon) VALUES ('Stop L', 39.234567, -73.012345);
INSERT INTO stop (name, lat, lon) VALUES ('Stop M', 40.012345, -74.123456);
INSERT INTO stop (name, lat, lon) VALUES ('Stop N', 41.345678, -75.234567);
INSERT INTO stop (name, lat, lon) VALUES ('Stop O', 39.789012, -73.345678);
