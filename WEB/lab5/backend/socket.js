 const socketio = require('socket.io');
const User = require('./models/user');
const messageController = require('./controllers/messageController');
const Message = require('./models/message');

module.exports = function (server) {
  const io = socketio(server, {
    cors: {
      origin: "*",
    }
  });

  io.on('connection', async (socket) => {
    console.log('User connected:', socket.id);

    // Get the logged in user's ID from the socket's query string
    const userId = socket.handshake.query.userId;

    // Get the user from the database
    const fromUser = await User.findById(userId);

    // If the user is not found, disconnect the socket
    if (!fromUser) {
      console.log('User not found');
      socket.disconnect();
      return;
    }

    // Join the room for this user's ID
    socket.join(userId);
    console.log('User join success. Id: ' + fromUser._id);

    // Listen for incoming chat messages
    socket.on('message', async (message) => {
      const { fromId, toId, content } = message;

      console.log('Message received:', message);

      // Get the user to send the message to from the database
      const toUser = await User.findById(toId);

      // If the user is not found, return an error message
      if (!toUser) {
        console.log('User not found');
        //callback('User not found');
        return;
      }

      const newMessage = new Message({
        fromId,
        toId,
        content,
      });

      await newMessage.save();

      var newMessageData = {
        fromId: newMessage.fromId,
        toId: newMessage.toId,
        fromLogin: fromUser.login,
        toLogin: toUser.login,
        content: newMessage.content
      };

      io.to(fromId).emit('message', newMessageData);
      io.to(toId).emit('message', newMessageData);
    });

    // Listen for disconnection events
    socket.on('disconnect', () => {
      console.log('User disconnected:', socket.id);
    });
  });
};
 
