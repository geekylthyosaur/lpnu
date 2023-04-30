const mongoose = require('mongoose');

const userSchema = new mongoose.Schema({
   _id: {
    type: mongoose.Schema.Types.ObjectId,
    auto: true,
  },
  unreadRoomIds: {
    type: [mongoose.Schema.Types.ObjectId],
    ref: 'Room',
  },
  username: {
    type: String,
    unique: true,
  },
  password: String,
});

const User = mongoose.model('User', userSchema, 'Users');

module.exports = User;
