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
    socket.on('getUnreadRooms', async (username) => {
      try {
        const user = await User.findOne({ username }).populate('unreadRoomIds').exec();
        if (!user) {
          return;
        }
        const unreadRooms = await Room.find({
          _id: { $in: user.unreadRoomIds },
          users: { $in: [username] }
        }).lean().exec();

        io.to(socket.id).emit('unreadRooms', unreadRooms);
      } catch (err) {
        console.error(err);
      }
    });

    socket.on('setRoomAsRead', async (roomId, username) => {
      try {
        const user = await User.findOne({ username });

        const room = await Room.findOne({ _id: roomId, users: { $in: [username] } });

        console.log('Setting room as read!');
        console.log(username, roomId);

        const updatedUser = await User.findByIdAndUpdate(user._id, { $pull: { unreadRoomIds: room._id } }, { new: true });
      } catch (err) {
        console.error(err);
      }
    });

    socket.on('getOldMessages', async (roomId) => {
      try {
        const room = await Room.findById(roomId).populate({ path: 'messages', populate: { path: 'senderId' }, options: { strictPopulate: false } }).exec();
        console.log('Getting old messages for room!');
        console.log(room);
        const messages = room.messages.map(message => {
          return {
            _id: message._id,
            senderId: message.senderId._id,
            author: message.senderId.username,
            isReadByToId: message.isReadByToId,
            content: message.content,
            createdAt: message.createdAt,
            updatedAt: message.updatedAt,
          }
        });
        io.to(roomId).emit('oldMessages', messages);
      } catch (err) {
        console.error(err);
      }
    });

    socket.on('newMessage', async (roomId, username, messageContent) => {
      const sender = await User.findOne({ username });
      if (!sender) {
        return console.error(`Sender ${username} not found`);
      }

      const message = new Message({ content: messageContent, senderId: sender._id });
      console.log('Got new message!');
      console.log(message);
      console.log(sender);

      try {
        const savedMessage = await message.save();
        const room = await Room.findById(roomId);
        room.messages.push(savedMessage._id);

        const connectedUsernames = Object.keys(io.sockets.adapter.rooms[roomId]?.sockets || {}).filter(socketId => socketId !== socket.id);
        const connectedUsers = await User.find({ username: { $in: connectedUsernames } });
        console.log(connectedUsers.map(u => u.username));

        const users = await User.find({ username: { $in: room.users } });
        const senderIndex = users.findIndex(user => user.username === sender.username);
        if (senderIndex !== -1) {
          users.splice(senderIndex, 1);
        }
        const nonConnectedUsers = users.filter(user => !connectedUsernames.includes(user.username));
        for (const user of nonConnectedUsers) {
          user.unreadRoomIds.addToSet(room._id);
          await user.save();
          console.log('Setting unread room for user!');
          console.log(user.username, room.name);
        }

        await room.save();
        io.to(roomId).emit('newMessage', sender.username, messageContent);
      } catch (error) {
        console.error(error);
      }
    });

    socket.on('joinRoom', (roomId) => {
      console.log(`Socket ${socket.id} joining room ${roomId}`);
      socket.join(roomId);
    });

    socket.on('leaveRoom', (roomId) => {
      console.log(`Socket ${socket.id} leaving room ${roomId}`);
      socket.leave(roomId);
    });
  });

  return io;
}

module.exports = init;

