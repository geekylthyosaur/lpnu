const mongoose = require('mongoose');

const userSchema = new mongoose.Schema({
   _id: {
    type: mongoose.Schema.Types.ObjectId,
    auto: true,
  },
  username: String,
  password: String,
});

const User = mongoose.model('User', userSchema, 'Users');

module.exports = User;
