const mongoose = require('mongoose');

const messageSchema = new mongoose.Schema({
  _id: {
    type: mongoose.Schema.Types.ObjectId,
    auto: true,
  },
  senderId: {
    type: mongoose.Schema.Types.ObjectId,
    ref: 'User',
  },
  isReadByToId: {
    type: mongoose.Schema.Types.Boolean,
    default: false,
  },
  content: String,
}, {
  timestamps: true,
});

const Message = mongoose.model('Message', messageSchema, 'Messages');

module.exports = {
  Message,
};

