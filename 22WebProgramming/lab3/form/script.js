const form = document.querySelector('form');
const errorMsg = document.getElementById('error-msg');

form.addEventListener('submit', (event) => {
  event.preventDefault();
  const username = document.getElementById('username').value;
  const password = document.getElementById('password').value;

  // Send the form data to login.php for validation
  const xhr = new XMLHttpRequest();
  xhr.open('POST', 'login.php', true);
  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
  xhr.onload = function () {
    if (xhr.status === 200) {
      if (xhr.responseText === 'success') {
        window.location.replace('home.html');
      } else {
        errorMsg.textContent = xhr.responseText;
      }
    }
  };
  xhr.send(`username=${username}&password=${password}`);
});

