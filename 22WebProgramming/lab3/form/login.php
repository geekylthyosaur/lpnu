<?php
// Check if the form has been submitted
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  // Get the user input from the form
  $username = trim($_POST['username']);
  $password = trim($_POST['password']);

  // Validate the user input
  $errorMsg = '';
  if (empty($username)) {
    $errorMsg = 'Please enter a username';
  } elseif (strlen($username) < 3) {
    $errorMsg = 'Username must be at least 3 characters long';
  } elseif (preg_match('/[^A-Za-z0-9]/', $username)) {
    $errorMsg = 'Username can only contain letters and numbers';
  }

  if (empty($password)) {
    $errorMsg = 'Please enter a password';
  } elseif (strlen($password) < 6) {
    $errorMsg = 'Password must be at least 6 characters long';
  }

  // Authenticate the user
  if (empty($errorMsg)) {
    // Replace this with your own authentication logic
    if ($username === 'myusername' && $password === 'mypassword') {
      echo 'success';
    } else {
      echo 'Invalid username or password';
    }
  } else {
    echo $errorMsg;
  }
}
?>

