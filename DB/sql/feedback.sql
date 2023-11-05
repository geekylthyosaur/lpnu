create table feedback
(
    id      serial
        constraint feedback_pk
            primary key,
    message text         not null,
    email   varchar(255) not null,
    name    varchar(64)  not null,
    time timestamp with time zone not null
);

alter table feedback
    owner to "user";

INSERT INTO feedback (message, email, name, time) VALUES
('Great service!', 'john@example.com', 'John Doe', '2023-11-04 10:00:00'),
('The website is very user-friendly.', 'susan@example.com', 'Susan Smith', '2023-11-04 10:15:00'),
('I had a wonderful experience.', 'mike@example.com', 'Mike Johnson', '2023-11-04 10:30:00'),
('Improvements needed in the product.', 'lisa@example.com', 'Lisa Brown', '2023-11-04 10:45:00'),
('Fast response from customer support.', 'robert@example.com', 'Robert Wilson', '2023-11-04 11:00:00'),
('The app crashes frequently.', 'emily@example.com', 'Emily Davis', '2023-11-04 11:15:00'),
('Outstanding service and support.', 'david@example.com', 'David Lee', '2023-11-04 11:30:00'),
('Product quality is top-notch.', 'jane@example.com', 'Jane Taylor', '2023-11-04 11:45:00'),
('An excellent experience overall.', 'william@example.com', 'William Turner', '2023-11-04 12:00:00'),
('The website is too slow.', 'sarah@example.com', 'Sarah Wright', '2023-11-04 12:15:00'),
('Prompt delivery and great packaging.', 'james@example.com', 'James Harris', '2023-11-04 12:30:00'),
('A few bugs in the mobile app.', 'linda@example.com', 'Linda Martinez', '2023-11-04 12:45:00'),
('Excellent customer service!', 'peter@example.com', 'Peter Scott', '2023-11-04 13:00:00'),
('User interface could be improved.', 'natalie@example.com', 'Natalie Turner', '2023-11-04 13:15:00'),
('The product is overpriced.', 'michael@example.com', 'Michael White', '2023-11-04 13:30:00');

