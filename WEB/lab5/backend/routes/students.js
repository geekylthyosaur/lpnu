const express = require('express');
const router = express.Router();
const studentController = require('../controllers/studentController');

// CREATE
router.post('/', studentController.createStudent);

// READ ALL
router.get('/', studentController.getAllStudents);

// UPDATE
router.put('/:id', studentController.updateStudent);

// DELETE
router.delete('/:id', studentController.deleteStudent);

module.exports = router;

