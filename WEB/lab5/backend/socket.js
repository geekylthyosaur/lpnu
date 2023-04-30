const Room = require('./models/room');
const { Message } = require('./models/message');
const User = require('./models/user');

const socketIO = require('socket.io');

function init(server) {
  const io = socketIO(server, {
    cors: {
      origin: '*',
      methods: ['GET', 'POST'],
    },
  });

  io.on('connection', (socket) => {
    socket.on('getOldMessages', async (roomId) => {
      try {
        const room = await Room.findById(roomId).populate('messages').exec();
        console.log('Getting old messages!');
        console.log(room.messages);
        console.log(room);
        socket.emit('oldMessages', room.messages);
      } catch (err) {
        console.error(err);
      }
    });

    socket.on('newMessage', async (roomId, username, messageContent) => {
      const sender = await User.findOne({ username });
      if (!sender) {
        return console.error(`Sender ${username} not found`);
      }

      const message = new Message({ content: messageContent, sender });
      try {
        const savedMessage = await message.save();
        const room = await Room.findById(roomId);
        room.messages.push(savedMessage._id);
        await room.save();
        socket.to(roomId).emit('newMessage', savedMessage);
      } catch (error) {
        console.error(error);
      }
    });

    socket.on('connect', async ({ roomId, userId }) => {
      socket.join(roomId);

      Room.findOne({ roomId }).sort({ timestamp: -1 }).exec((err, messages) => {
        if (err) {
          return console.error(err);
        }
        socket.emit('loadMessages', messages.reverse());
      });
    });
  });

  return io;
}

module.exports = init;

