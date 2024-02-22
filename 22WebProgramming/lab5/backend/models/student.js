const mongoose = require('mongoose');

const studentSchema = new mongoose.Schema({
   _id: {
    type: mongoose.Schema.Types.ObjectId,
    auto: true,
  },
  group: String,
  name: String,
  gender: String,
  birthday: Date,
  status: String
});

const Student = mongoose.model('Student', studentSchema, 'Students');

module.exports = Student;

