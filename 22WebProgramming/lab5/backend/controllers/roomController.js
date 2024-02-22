const Room = require('../models/room');
const User = require('../models/user');
const Message = require('../models/message');

async function createRoom(req, res) {
  try {
    const { name, users } = req.body;
    const room = new Room({
      name,
      users,
    });
    await room.save();

    console.log("Creating room!");
    console.log(room);

    res.status(201).json({ message: 'Room created successfully.' });
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: 'Server error.' });
  }
}

async function getRoomWithUser(req, res) {
  try {
    const { username } = req.params;
    const room = await Room.find({ users: { $in: [username] } }).lean().exec();

    console.log("Getting room with username!");
    console.log(room);

    res.status(200).json(room);
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: 'Server error.' });
  }
}

async function getUnreadRooms(req, res) {
  try {
    const { username } = req.params;
    const user = await User.findOne({ username }).populate('unreadRoomIds').exec();
    if (!user) {
      return res.status(404).json({ message: 'User not found.' });
    }
    const unreadRooms = await Room.find({
      _id: { $in: user.unreadRoomIds },
      users: { $in: [username] }
    }).lean().exec();

    console.log('Getting unread rooms!');
    console.log(unreadRooms);

    res.status(200).json(unreadRooms);
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: 'Server error.' });
  }
}

async function setRoomAsRead(req, res) {
  try {
    const { roomId, username } = req.params;

    const user = await User.findOne({ username });
    if (!user) {
      return res.status(404).json({ message: 'User not found' });
    }

    const room = await Room.findOne({ _id: roomId, users: { $in: [username] } });
    if (!room) {
      return res.status(404).json({ message: 'Room not found or user is not a member' });
    }

    const updatedUser = await User.findByIdAndUpdate(user._id, { $pull: { unreadRoomIds: room._id } }, { new: true });
    if (!updatedUser) {
      return res.status(500).json({ message: 'Failed to update user' });
    }

    res.status(200).json({ message: 'Room marked as read for user' });
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: 'Server error' });
  }
}

async function getRoomById(req, res) {
  try {
    const { roomid } = req.params;
    console.log(roomid);
    const room = await Room.findOne({ _id: roomid }).lean().exec();

    console.log("Getting room by id!");
    console.log(room);

    res.status(200).json(room);
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: 'Server error.' });
  }
}

async function deleteUserFromRoom(req, res) {
    try {
    const { roomid, username } = req.params;

    const room = await Room.findByIdAndUpdate(roomid, { $pull: { users: username } }, { new: true }).lean().exec();

    console.log("Deleting user from room!");
    console.log(roomid);
    console.log(username);
    console.log(room);

    if (!room) {
      return res.status(404).json({ message: 'Room not found.' });
    }

    res.status(200).json(room);
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: 'Server error.' });
  }
}

module.exports = {
  createRoom,
  getRoomWithUser,
  getRoomById,
  getUnreadRooms,
  setRoomAsRead,
  deleteUserFromRoom,
};

