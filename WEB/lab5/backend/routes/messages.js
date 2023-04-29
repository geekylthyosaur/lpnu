const express = require('express');
const router = express.Router();
const messageController = require('../controllers/messageController');

router.post('/', messageController.createMessage);
router.get('/all', messageController.getAllMessages);
router.get('/', messageController.getMessagesByIds);
router.get('/unread/', messageController.getUnreadMessagesByReceiverId);

module.exports = router;

