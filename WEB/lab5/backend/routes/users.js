const express = require('express');
const router = express.Router();
const userController = require('../controllers/userController');

router.post('/signup', userController.signUpUser);
router.post('/login', userController.signInUser);
router.get('/all', userController.getAllUsers);

module.exports = router;

