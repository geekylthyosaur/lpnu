const express = require('express');
const router = express.Router();
const roomController = require('../controllers/roomController');

router.post('/', roomController.createRoom);
router.get('/all/:username', roomController.getRoomWithUser);
router.get('/:roomid', roomController.getRoomById);
router.delete('/:roomid/:username', roomController.deleteUserFromRoom);

module.exports = router;

