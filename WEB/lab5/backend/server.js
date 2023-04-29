const express = require('express');
const mongoose = require('mongoose');
const jwt = require('jsonwebtoken');
const cors = require('cors');

const app = express();

app.use(cors());
app.use(express.json());

const PORT = 3000;
const MONGODB_URI = 'mongodb://localhost:27018/students';

mongoose.connect(MONGODB_URI, { useNewUrlParser: true, useUnifiedTopology: true })
  .then(() => console.log('Connected to MongoDB'))
  .catch(err => console.error(err));

const studentSchema = new mongoose.Schema({
  id: String,
  group: String,
  name: String,
  gender: String,
  birthday: Date,
  status: { type: Number, default: 0 },
});

const Student = mongoose.model('Student', studentSchema);

const userSchema = new mongoose.Schema({
  username: String,
  password: String,
});

const User = mongoose.model('User', userSchema);

app.post('/signup', async (req, res) => {
  const { username, password } = req.body;
  const user = new User({ username, password });
  await user.save();
  console.log("Creating user!");
  console.log(user);
  res.json({ message: 'User created' });
});

app.post('/login', async (req, res) => {
  const { username, password } = req.body;
  const user = await User.findOne({ username });
  if (!user) return res.status(404).json({ message: 'User not found' });
  if (user.password !== password) return res.status(401).json({ message: 'Invalid password' });
  const token = jwt.sign({ userId: user._id }, 'secretkey');
  console.log("Logging in user!");
  console.log(user);
  res.json({ token });
});

app.get('/students', async (req, res) => {
  const students = await Student.find({}).lean().exec();
  console.log("Getting students!");
  console.log(students);
  res.json(students);
});

app.get('/students/:id', async (req, res) => {
  const { id } = req.params;
  const student = await Student.findById(id).lean().exec();
  console.log("Getting student!");
  console.log(student);
  res.json(student);
});

app.post('/students', async (req, res) => {
  const student = new Student(req.body);
  console.log("Creating new student!");
  console.log(student);
  await student.save();
  res.json(student);
});

app.put('/students/:id', async (req, res) => {
  const { id } = req.params;
  const student = await Student.findByIdAndUpdate(id, req.body, { new: true }).lean().exec();
  console.log("Editing student!");
  console.log(student);
  res.json(student);
});

app.delete('/students/:id', async (req, res) => {
  const { id } = req.params;
  const student = await Student.findByIdAndDelete(id).lean().exec();
  console.log("Deleting student!");
  console.log(student);
  res.json(student);
});

app.listen(PORT, () => console.log(`Server started on port ${PORT}`));

