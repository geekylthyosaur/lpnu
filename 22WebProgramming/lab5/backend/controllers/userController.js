const User = require('../models/user');
const jwt = require('jsonwebtoken');

const secretKey = 'secretKey';

async function signInUser(req, res) {
  const { username, password } = req.body;
  const user = await User.findOne({ username });
  if (!user) return res.status(404).json({ message: 'User not found' });
  if (user.password !== password) return res.status(401).json({ message: 'Invalid password' });
  const token = jwt.sign({ userId: user._id }, secretKey);
  console.log("Logging in user!");
  console.log(user);
  res.json({ 'token': token });
}

async function signUpUser(req, res) {
  const { username, password } = req.body;
  const user = new User({ username, password });
  await user.save();
  console.log("Creating user!");
  console.log(user);
  const token = jwt.sign({ userId: user._id }, secretKey);
  res.json({ 'token': token });
}

async function getAllUsers(req, res) {
  try {
    const users = await User.find({});
    res.send(users);
  } catch (err) {
    console.log(err);
    res.status(500).send(err);
  }
}

module.exports = {
    signInUser,
    signUpUser,
    getAllUsers,
};
