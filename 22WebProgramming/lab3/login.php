<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  $username = trim($_POST['username']);
  $password = trim($_POST['password']);

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

  if (empty($errorMsg)) {
    if ($username === 'myusername' && $password === 'mypassword') {
      echo 'success';
      http_response_code(200);
    } else {
      echo 'Invalid username or password';
      http_response_code(401);
    }
  } else {
    http_response_code(401);
    echo $errorMsg;
  }
}
?>


