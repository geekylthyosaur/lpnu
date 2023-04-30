const express = require('express');
const cors = require('cors');
const mongoose = require('mongoose');
const http = require('http');
const socket = require('./socket');

const connectionString = 'mongodb://localhost:27018/db';

mongoose.connect(connectionString);

const db = mongoose.connection;
db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function () {
    console.log("StudentDB connected");

    const app = express();
    const httpsPort = 3000;
    const httpPort = 3080;
    const studentsRouter = require('./routes/students');
    const userRouter = require('./routes/users');
    const messagesRouter = require('./routes/messages');
    const roomsRouter = require('./routes/rooms');
    const tasksRouter = require('./routes/tasks');

    app.use(cors());
    app.use(express.json());
    app.use('/students', studentsRouter);
    app.use('/', userRouter);
    app.use('/messages', messagesRouter);
    app.use('/rooms', roomsRouter);
    app.use('/tasks', tasksRouter);

    const server = http.createServer(app);
    socket(server);

    app.listen(httpsPort, () => console.log(`Server started on httpsPort ${httpsPort}`));
    server.listen(httpPort, () => console.log(`Socket started on httpsPort ${httpPort}`));
});

