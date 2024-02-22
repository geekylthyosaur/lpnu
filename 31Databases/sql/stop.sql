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

INSERT INTO stop (name, lat, lon) VALUES ('Central Station', 40.123456, -74.654321);
INSERT INTO stop (name, lat, lon) VALUES ('City Park', 41.987654, -75.123456);
INSERT INTO stop (name, lat, lon) VALUES ('Main Street', 39.567890, -73.987654);
INSERT INTO stop (name, lat, lon) VALUES ('Riverfront Plaza', 40.765432, -74.234567);
INSERT INTO stop (name, lat, lon) VALUES ('Park Avenue', 41.234567, -75.345678);
INSERT INTO stop (name, lat, lon) VALUES ('Downtown Square', 39.876543, -73.456789);
INSERT INTO stop (name, lat, lon) VALUES ('Station Road', 40.345678, -74.567890);
INSERT INTO stop (name, lat, lon) VALUES ('Hillside Park', 41.654321, -75.678901);
INSERT INTO stop (name, lat, lon) VALUES ('Harbor View', 39.432109, -73.789012);
INSERT INTO stop (name, lat, lon) VALUES ('Beachfront Drive', 40.789012, -74.890123);
INSERT INTO stop (name, lat, lon) VALUES ('Lakeside Avenue', 41.567890, -75.901234);
INSERT INTO stop (name, lat, lon) VALUES ('Eastwood Lane', 39.234567, -73.012345);
INSERT INTO stop (name, lat, lon) VALUES ('Maple Street', 40.012345, -74.123456);
INSERT INTO stop (name, lat, lon) VALUES ('Sunset Boulevard', 41.345678, -75.234567);
INSERT INTO stop (name, lat, lon) VALUES ('Grove Park', 39.789012, -73.345678);
