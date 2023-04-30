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
    type: [{ type: mongoose.Schema.Types.ObjectId, ref: 'Message' }],
    default: [],
  },
}, {
  timestamps: true,
});

const Room = mongoose.model('Room', roomSchema, 'Rooms');

module.exports = Room;

