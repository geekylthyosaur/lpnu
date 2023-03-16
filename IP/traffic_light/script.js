setTimeout(function() {
  document.querySelector('.red-light').style.opacity = 1;
  document.querySelector('.yellow-light').style.opacity = 0.1;
  document.querySelector('.green-light').style.opacity = 0.1;
}, 0);

setTimeout(function() {
  document.querySelector('.red-light').style.opacity = 1;
  document.querySelector('.yellow-light').style.opacity = 1;
  document.querySelector('.green-light').style.opacity = 0.1;
}, 3000);

setTimeout(function() {
  document.querySelector('.red-light').style.opacity = 0.1;
  document.querySelector('.yellow-light').style.opacity = 0.1;
  document.querySelector('.green-light').style.opacity = 1;
}, 5000);
