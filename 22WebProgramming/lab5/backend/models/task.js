const mongoose = require('mongoose');

const taskSchema = new mongoose.Schema({
  _id: {
    type: mongoose.Schema.Types.ObjectId,
    auto: true,
  },
  title: {
    type: String,
  },
  state: {
    type: String,
  },
}, {
  timestamps: true,
});

const Task = mongoose.model('Task', taskSchema, 'Tasks');

module.exports = Task;

