const express = require('express');
const app = express();
const server = require('http').Server(app);
const io = require('socket.io')(server);
const mongoose = require('mongoose');
require('dotenv').config();

const uri = process.env.MONGODB_URI;

mongoose.connect(uri, {
  useNewUrlParser: true,
  useUnifiedTopology: true,
});

mongoose.connection.on('connected', () => {
  console.log('Connected to MongoDB!');
});

mongoose.connection.on('error', (err) => {
  console.error(`Error connecting to MongoDB: ${err}`);
});
const MessageSchema = mongoose.Schema({
  name: String,
  message: String
});

const Message = mongoose.model('Message', MessageSchema);

app.use(express.static(__dirname + '/public'));

app.get('/', function(req, res) {
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', async function(socket) {
  console.log('a user connected');

  const messages = await Message.find({}).exec();
  socket.emit('load messages', messages);

  socket.on('disconnect', function() {
    console.log('user disconnected');
  });

  socket.on('chat message', function(msg) {
    console.log('message: ' + msg);

    const message = new Message({ name: 'Anonymous', message: msg });
    message.save();

    io.emit('chat message', msg);
  });
});

server.listen(3000, function() {
  console.log('listening on *:3000');
});

