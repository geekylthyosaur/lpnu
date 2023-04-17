<?php

$servername = "127.0.0.1:3306";
$username = "root";
$password = "password";

// Create connection
$conn = new mysqli($servername, $username, $password);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
echo "Connected successfully";

$sql = "CREATE DATABASE db;";

if (mysqli_query($conn, $sql)) {
    echo "Table created successfully";
} else {
    echo "Error creating database: " . mysqli_error($conn);
}
$conn->close();

$db = "db";
$conn = mysqli_connect($servername, $username, $password, $db);

$sql = "CREATE TABLE students (
    id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    class VARCHAR(30) NOT NULL,
    name VARCHAR(30) NOT NULL,
    gender VARCHAR(30) NOT NULL,
    birthday VARCHAR(30) NOT NULL,
    status VARCHAR(30) NOT NULL
);";
if (mysqli_query($conn, $sql)) {
    echo "Table created successfully";
} else {
    echo "Error creating table: " . mysqli_error($conn);
}

// Add
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  $json = file_get_contents('php://input');
  $student = json_decode($json);

  $id = trim($student->id);
  $group = trim($student->group);
  $name = trim($student->name);
  $gender = trim($student->gender);
  $birthday = trim($student->birthday);
  $status = trim($student->status);

  $errors = [];

  if (empty($id)) {
    $errors[] = 'ID is required.';
  }

  if (empty($group)) {
    $errors[] = 'Group is required.';
  }

  if (empty($name) || strlen($name) < 5) {
    $errors[] = 'Name is required and should be at least 5 characters in length.';
  }

  if (empty($gender) || !in_array($gender, ['Male', 'Female', 'Other'])) {
    $errors[] = 'Gender is required and must be "male", "female", or "other".';
  }

  if (empty($birthday)) {
    $errors[] = 'Birthday is required.';
  } elseif (!preg_match('/^\d{4}-\d{2}-\d{2}$/', $birthday)) {
    $errors[] = 'Birthday must be in the format "YYYY-MM-DD".';
  }

  if (empty($status) || !in_array($status, ['0', '1'])) {
    $errors[] = 'Status is required and must be "0" or "1".';
  }

  if (!empty($errors)) {
    http_response_code(400);
    echo json_encode(['errors' => $errors]);
    exit;
  } else {
    http_response_code(200);
    exit;
  }
}

// PUT
if ($_SERVER['REQUEST_METHOD'] === 'PUT') {
  $json = file_get_contents('php://input');
  $student = json_decode($json);

  $id = trim($student->id);
  $group = trim($student->group);
  $name = trim($student->name);
  $gender = trim($student->gender);
  $birthday = trim($student->birthday);
  $status = trim($student->status);

  $errors = [];

  if (empty($id)) {
    $errors[] = 'ID is required.';
  }

  if (empty($group)) {
    $errors[] = 'Group is required.';
  }

  if (empty($name) || strlen($name) < 5) {
    $errors[] = 'Name is required and should be at least 5 characters in length.';
  }

  if (empty($gender) || !in_array($gender, ['Male', 'Female', 'Other'])) {
    $errors[] = 'Gender is required and must be "male", "female", or "other".';
  }

  if (empty($birthday)) {
    $errors[] = 'Birthday is required.';
  } elseif (!preg_match('/^\d{4}-\d{2}-\d{2}$/', $birthday)) {
    $errors[] = 'Birthday must be in the format "YYYY-MM-DD".';
  }

  if (empty($status) || !in_array($status, ['0', '1'])) {
    $errors[] = 'Status is required and must be "0" or "1".';
  }

  if (!empty($errors)) {
    http_response_code(400);
    echo json_encode(['errors' => $errors]);
    exit;
  } else {
    http_response_code(200);
    exit;
  }
}

// Delete
if ($_SERVER['REQUEST_METHOD'] === 'DELETE') {
  $json = file_get_contents('php://input');
  $student = json_decode($json);

  $id = trim($student->id);
  $group = trim($student->group);
  $name = trim($student->name);
  $gender = trim($student->gender);
  $birthday = trim($student->birthday);
  $status = trim($student->status);

  $errors = [];

  if (empty($id)) {
    $errors[] = 'ID is required.';
  }

  if (empty($group)) {
    $errors[] = 'Group is required.';
  }

  if (empty($name) || strlen($name) < 5) {
    $errors[] = 'Name is required and should be at least 5 characters in length.';
  }

  if (empty($gender) || !in_array($gender, ['Male', 'Female', 'Other'])) {
    $errors[] = 'Gender is required and must be "male", "female", or "other".';
  }

  if (empty($birthday)) {
    $errors[] = 'Birthday is required.';
  } elseif (!preg_match('/^\d{4}-\d{2}-\d{2}$/', $birthday)) {
    $errors[] = 'Birthday must be in the format "YYYY-MM-DD".';
  }

  if (empty($status) || !in_array($status, ['0', '1'])) {
    $errors[] = 'Status is required and must be "0" or "1".';
  }

  if (!empty($errors)) {
    http_response_code(400);
    echo json_encode(['errors' => $errors]);
    exit;
  } else {
    http_response_code(200);
    exit;
  }
}
?>
