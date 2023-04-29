const Message = require('../models/message');
const User = require('../models/user');

async function createMessage(req, res) {
  try {
    const { fromId, toId, content } = req.body;
    const message = new Message({
      fromId,
      toId,
      content,
    });
    await message.save();
    res.status(201).json({ message: 'Message created successfully.' });
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: 'Server error.' });
  }
}

async function getAllMessages(req, res) {
  try {
    const messages = await Message.find().sort({ createdAt: 1 });
    const messagesData = [];

    for (const message of messages) {
      const fromUser = await User.findById(message.fromId);
      const toUser = await User.findById(message.toId);

      messagesData.push({
        fromId: message.fromId,
        toId: message.toId,
        fromLogin: fromUser.login,
        toLogin: toUser.login,
        content: message.content
      });
    }

    res.status(200).json(messagesData);
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: 'Server error.' });
  }
}

async function getMessagesByIds(req, res) {
  try {
    const userOneId = req.query.userOneId;
    const userTwoId = req.query.userTwoId;

    const messages = await Message.find({
      $or: [
        { fromId: userOneId, toId: userTwoId },
        { fromId: userTwoId, toId: userOneId },
      ],
    }).sort({ createdAt: 1 }).exec();
    const messagesData = [];

    for (const message of messages) {
      const fromUser = await User.findById(message.fromId);
      const toUser = await User.findById(message.toId);

      messagesData.push({
        fromId: message.fromId,
        toId: message.toId,
        fromLogin: fromUser.login,
        toLogin: toUser.login,
        content: message.content
      });
    }

    await setMessagesToRead(userTwoId);

    res.status(200).json(messagesData);
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: 'Server error' });
  }
}

async function getUnreadMessagesByReceiverId(req, res) {
  try {
    const userRecieverId = req.query.userRecieverId;

    const messages = await Message.find({ toId: userRecieverId, isReadByToId: false }).sort({ createdAt: 1 }).exec();
    const messagesData = [];

    for (const message of messages) {
      const fromUser = await User.findById(message.fromId);
      const toUser = await User.findById(message.toId);

      messagesData.push({
        fromLogin: fromUser.login,
        content: message.content
      });
    }

    res.status(200).json(messagesData);
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: 'Server error' });
  }
}

async function setMessagesToRead(currentUserId) {
  const resultUpdateIsRead = await Message.updateMany({ toId: currentUserId, isReadByToId: false }, { $set: { isReadByToId: true } });
  console.log('Update IsRead for user ' + currentUserId);
  console.log('Mathced count: ' + resultUpdateIsRead.matchedCount);
  console.log('Updated count: ' + resultUpdateIsRead.matchedCount);
}

module.exports = {
  createMessage,
  getAllMessages,
  getMessagesByIds,
  getUnreadMessagesByReceiverId,
};

