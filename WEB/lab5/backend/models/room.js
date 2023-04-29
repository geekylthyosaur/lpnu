const mongoose = require('mongoose');

const roomSchema = new mongoose.Schema({
  _id: {
    type: mongoose.Schema.Types.ObjectId,
    auto: true,
  },
  name: {
    type: String,
  },
  users: {
    type: [String],
  },
  messages: {
    type: [mongoose.Schema.Types.ObjectId],
    default: [],
  },
}, {
  timestamps: true,
});

const Room = mongoose.model('Room', roomSchema, 'Rooms');

module.exports = Room;

