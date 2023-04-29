const express = require('express');
const router = express.Router();
const roomController = require('../controllers/roomController');

router.post('/', roomController.createRoom);
router.get('/:username', roomController.getRoomWithUser);
router.delete('/:roomid/:username', roomController.deleteUserFromRoom);

module.exports = router;

