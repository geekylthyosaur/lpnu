const express = require('express');
const router = express.Router();
const taskController = require('../controllers/taskController');

router.post('/', taskController.createTask);
router.put('/:id', taskController.updateTask);
router.get('/', taskController.getAllTasks);
router.delete('/:id', taskController.deleteTask);

module.exports = router;

