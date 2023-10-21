create table feedback
(
    id      serial
        constraint feedback_pk
            primary key,
    message text         not null,
    email   varchar(255) not null,
    name    varchar(64)  not null
);

alter table feedback
    owner to "user";

INSERT INTO feedback (message, email, name) VALUES ('Great service!', 'john@example.com', 'John Doe');
INSERT INTO feedback (message, email, name) VALUES ('The website is very user-friendly.', 'susan@example.com', 'Susan Smith');
INSERT INTO feedback (message, email, name) VALUES ('I had a wonderful experience.', 'mike@example.com', 'Mike Johnson');
INSERT INTO feedback (message, email, name) VALUES ('Improvements needed in the product.', 'lisa@example.com', 'Lisa Brown');
INSERT INTO feedback (message, email, name) VALUES ('Fast response from customer support.', 'robert@example.com', 'Robert Wilson');
INSERT INTO feedback (message, email, name) VALUES ('The app crashes frequently.', 'emily@example.com', 'Emily Davis');
INSERT INTO feedback (message, email, name) VALUES ('Outstanding service and support.', 'david@example.com', 'David Lee');
INSERT INTO feedback (message, email, name) VALUES ('Product quality is top-notch.', 'jane@example.com', 'Jane Taylor');
INSERT INTO feedback (message, email, name) VALUES ('An excellent experience overall.', 'william@example.com', 'William Turner');
INSERT INTO feedback (message, email, name) VALUES ('The website is too slow.', 'sarah@example.com', 'Sarah Wright');
INSERT INTO feedback (message, email, name) VALUES ('Prompt delivery and great packaging.', 'james@example.com', 'James Harris');
INSERT INTO feedback (message, email, name) VALUES ('A few bugs in the mobile app.', 'linda@example.com', 'Linda Martinez');
INSERT INTO feedback (message, email, name) VALUES ('Excellent customer service!', 'peter@example.com', 'Peter Scott');
INSERT INTO feedback (message, email, name) VALUES ('User interface could be improved.', 'natalie@example.com', 'Natalie Turner');
INSERT INTO feedback (message, email, name) VALUES ('The product is overpriced.', 'michael@example.com', 'Michael White');
