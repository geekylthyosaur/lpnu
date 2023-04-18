drawTable();
let isLoggedIn = 0;
let loggedInUser = "";
let students = []
let globalStudentId = 1;
let studentIdToDelete = 0;
let studentIdToEdit = 0;
// Checkboxes
const checkAll = document.getElementById("check-all");

const loginButton = document.getElementById("login-button");
loginButton.addEventListener("click", () => {
  const loginForm = document.getElementById("login-form-wrapper");
  loginForm.style.display = "block";
});

const loginForm = document.getElementById("login-form-wrapper");
const errorMsg = document.getElementById('error-msg');
loginForm.addEventListener('submit', (event) => {
  event.preventDefault();
  const username = document.getElementById('username').value;
  const password = document.getElementById('password').value;

  const xhr = new XMLHttpRequest();
  xhr.open('POST', 'login.php', true);
  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
  xhr.onload = function () {
    if (xhr.status === 200) {
      loginForm.style.display = "none";
      loggedInUser = username;
      isLoggedIn = 1;
      const user = document.getElementById("user");
      const login = document.getElementById("login");
      user.style.display = "flex";
      login.style.display = "none";
      userName.innerHTML = loggedInUser;
    } else {
      errorMsg.textContent = xhr.responseText;
      const user = document.getElementById("user");
      const login = document.getElementById("login");
      user.style.display = "none";
      login.style.display = "block";
    };
  };
  xhr.send(`username=${username}&password=${password}`);
});

const userName = document.getElementById("user-name");

if (isLoggedIn === 1) {
  const user = document.getElementById("user");
  const login = document.getElementById("login");
  user.style.display = "flex";
  login.style.display = "none";
  userName.innerHTML = loggedInUser;
} else {
  const user = document.getElementById("user");
  const login = document.getElementById("login");
  user.style.display = "none";
  login.style.display = "block";
}

checkAll.addEventListener("click", () => {
  const checkboxes = document.querySelectorAll(".check");
  checkboxes.forEach((checkbox) => {
    checkbox.checked = checkAll.checked;
  });
});


const logoutButton = document.getElementById("logout-button");

logoutButton.addEventListener('click', () => {
  isLoggedIn = 0;
  loggedInUser = "";
  if (isLoggedIn === 1) {
    const user = document.getElementById("user");
    const login = document.getElementById("login");
    user.style.display = "flex";
    login.style.display = "none";
    userName.innerHTML = loggedInUser;
  } else {
    const user = document.getElementById("user");
    const login = document.getElementById("login");
    user.style.display = "none";
    login.style.display = "block";
  }
});


// Delete row of table && warning modal
const warningModal = document.getElementById("warning-modal-wrapper");
const warningCloseBtn = document.getElementById("warning-modal-close");
const warningCancelBtn = document.getElementById("warning-modal-cancel");

warningCloseBtn.addEventListener('click', () => {
  warningModal.style.display = "none";
});

warningCancelBtn.addEventListener('click', () => {
  warningModal.style.display = "none";
});

const warningDeleteBtn = document.getElementById("warning-modal-delete");
warningDeleteBtn.addEventListener("click", () => {
  const xhr = new XMLHttpRequest();
  console.log(studentIdToDelete);
  xhr.open('DELETE', '/students/' + studentIdToDelete, true);
  xhr.setRequestHeader('Content-Type', 'application/json');
  xhr.setRequestHeader('X-CSRF-TOKEN', document.querySelector('input[name="_token"]').value);
  xhr.onload = function () {
    console.log(xhr.responseText);
    if (xhr.status === 200) {
      const errorContainer = document.getElementById('error-container');
      while (errorContainer.firstChild) {
        errorContainer.removeChild(errorContainer.firstChild);
      }
      addModal.style.display = "none";

      clearTable();
      drawTable();
      addForm.reset();
    } else {
      const response = JSON.parse(xhr.responseText);
      if (response.errors) {
        const errorContainer = document.getElementById('error-container');
        errorContainer.innerHTML = '';
        response.errors.forEach(function (error) {
          const errorMessage = document.createElement('p');
          errorMessage.textContent = error;
          errorContainer.appendChild(errorMessage);
        });
      }
    }
  };
  xhr.send();
  clearTable();
  drawTable();
  warningModal.style.display = "none";
  studentIdToDelete = 0;
})


// Add row to table && add modal
const addBtn = document.getElementById("add-row");
const addModal = document.getElementById("add-modal-wrapper");
const addModalCloseBtn = document.getElementById("add-modal-close");
const addModalOkBtn = document.getElementById("add-modal-create");
const addForm = document.getElementById("add-form");

addBtn.addEventListener("click", () => {
  const a = document.getElementById("add-form-title");
  const b = document.getElementById("add-modal-create");
  a.innerHTML = "Add Student";
  b.innerHTML = "Add";
  addModal.style.display = "block";
})

addModalCloseBtn.addEventListener('click', () => {
      const errorContainer = document.getElementById('error-container');
      while (errorContainer.firstChild) {
        errorContainer.removeChild(errorContainer.firstChild);
      }
  addModal.style.display = "none";
  const invalids = document.querySelectorAll(".invalid");
  invalids.forEach((invalid) => {
    invalid.classList.remove("invalid");
  });
  addForm.reset();
});

function validateStudent(student) {
  valid = true;

  const fieldGroup = document.getElementById("add-form-field-group");
  const fieldFirstName = document.getElementById("add-form-field-firstName");
  const fieldLastName = document.getElementById("add-form-field-lastName");
  const fieldGender = document.getElementById("add-form-field-gender");
  const fieldBirthday = document.getElementById("add-form-field-birthday");

  const birthday = new Date(student.birthday);
  if (isNaN(birthday.getTime()) || birthday > new Date()) {
    fieldBirthday.classList.add("invalid");
    valid = false;
  } else {
    fieldBirthday.classList.remove("invalid");
  }
  return valid;
}

function addStudent() {
  const i = students.findIndex(s => s.id === studentIdToEdit);
  const fieldId = document.getElementById("add-form-field-id");
  const fieldGroup = document.getElementById("add-form-field-group");
  const fieldFirstName = document.getElementById("add-form-field-firstName");
  const fieldLastName = document.getElementById("add-form-field-lastName");
  const fieldGender = document.getElementById("add-form-field-gender");
  const fieldBirthday = document.getElementById("add-form-field-birthday");
  const id = fieldId.value;
  const first_name = fieldFirstName.value;
  const last_name = fieldLastName.value;
  const group = fieldGroup.options[fieldGroup.selectedIndex].textContent;
  const gender = fieldGender.options[fieldGender.selectedIndex].textContent;
  const birthday = fieldBirthday.value;

  const student = {
    "id": id,
    "group": group,
    "first_name": first_name,
    "last_name": last_name,
    "gender": gender,
    "birthday": birthday,
    "status": 1,
  };

  if (!validateStudent(student)) {
    return;
  }

  const xhr = new XMLHttpRequest();
  xhr.open('POST', '/students', true);
  xhr.setRequestHeader('Content-Type', 'application/json');
  xhr.setRequestHeader('X-CSRF-TOKEN', document.querySelector('input[name="_token"]').value);
  xhr.onload = function () {
    console.log(xhr.responseText);
    if (xhr.status === 200) {
      const errorContainer = document.getElementById('error-container');
      while (errorContainer.firstChild) {
        errorContainer.removeChild(errorContainer.firstChild);
      }
      addModal.style.display = "none";

      students.push(student);

      clearTable();
      drawTable();
      addForm.reset();
    } else {
      const response = JSON.parse(xhr.responseText);
      if (response.errors) {
        const errorContainer = document.getElementById('error-container');
        errorContainer.innerHTML = '';
        response.errors.forEach(function (error) {
          const errorMessage = document.createElement('p');
          errorMessage.textContent = error;
          errorContainer.appendChild(errorMessage);
        });
      }
    }
  };
  xhr.send(JSON.stringify(student));
}

function editStudent(studentId) {
  const i = students.findIndex(s => s.id === studentIdToEdit);
  const fieldId = document.getElementById("add-form-field-id");
  const fieldGroup = document.getElementById("add-form-field-group");
  const fieldFirstName = document.getElementById("add-form-field-firstName");
  const fieldLastName = document.getElementById("add-form-field-lastName");
  const fieldGender = document.getElementById("add-form-field-gender");
  const fieldBirthday = document.getElementById("add-form-field-birthday");
  const id = fieldId.value;
  const first_name = fieldFirstName.value;
  const last_name = fieldLastName.value;
  const group = fieldGroup.options[fieldGroup.selectedIndex].textContent;
  const gender = fieldGender.options[fieldGender.selectedIndex].textContent;
  const birthday = fieldBirthday.value;

  console.log(birthday);

  const student = {
    "id": id,
    "group": group,
    "first_name": first_name,
    "last_name": last_name,
    "gender": gender,
    "birthday": birthday,
    "status": 1,
  };

  if (!validateStudent(student)) {
    return;
  }

  const xhr = new XMLHttpRequest();
  xhr.open('PUT', '/students/' + studentIdToEdit, true);
  xhr.setRequestHeader('Content-Type', 'application/json');
  xhr.setRequestHeader('X-CSRF-TOKEN', document.querySelector('input[name="_token"]').value);
  xhr.onload = function () {
    if (xhr.status === 200) {
      const errorContainer = document.getElementById('error-container');
      while (errorContainer.firstChild) {
        errorContainer.removeChild(errorContainer.firstChild);
      }
      addModal.style.display = "none";

      clearTable();
      drawTable();
      addForm.reset();
    } else {
      console.log(xhr.responseText);
      const response = JSON.parse(xhr.responseText);
      if (response.errors) {
        const errorContainer = document.getElementById('error-container');
        errorContainer.innerHTML = '';
        response.errors.forEach(function (error) {
          const errorMessage = document.createElement('p');
          errorMessage.textContent = error;
          errorContainer.appendChild(errorMessage);
        });
      }
    }
  };
  xhr.send(JSON.stringify(student));
  studentIdToEdit = 0;
}

window.onclick = function (event) {
  if (event.target === addModal) {
    addModal.style.display = "none";
  }
};

addModalOkBtn.addEventListener('click', () => {
  const e = document.getElementById("add-form-title");
  if (e.innerHTML === "Edit Student") {
    editStudent();
  } else {
    addStudent();
  }
});

// Profile && notification headers
const profileHeaderTrigger = document.getElementById("profile-header-trigger");
const profileHeader = document.getElementById("profile-header");
const notificationHeaderTrigger = document.getElementById("notification-header-trigger");
const notificationHeader = document.getElementById("notification-header");

profileHeaderTrigger.addEventListener('mouseover', function () {
  profileHeader.classList.add('active');
});

profileHeader.addEventListener('mouseleave', function () {
  profileHeader.classList.remove('active');
});

document.addEventListener('click', function (event) {
  if (!profileHeaderTrigger.contains(event.target) && !profileHeader.contains(event.target)) {
    profileHeader.classList.remove('active');
  }
});

notificationHeaderTrigger.addEventListener('mouseover', function () {
  notificationHeader.classList.add('active');
});

notificationHeader.addEventListener('mouseleave', function () {
  notificationHeader.classList.remove('active');
});

document.addEventListener('click', function (event) {
  if (!notificationHeaderTrigger.contains(event.target) && !notificationHeader.contains(event.target)) {
    notificationHeader.classList.remove('active');
  }
});

function drawTable() {
  const table = document.getElementById("table");
  fetch('/students')
    .then(response => response.json())
    .then(data => {
      data.students.forEach(student => {
        const newRow = table.insertRow();
        newRow.id = student.id;
        const checkboxCell = newRow.insertCell();
        const checkbox = document.createElement("input");
        checkbox.type = "checkbox";
        checkbox.className = "check";
        checkboxCell.appendChild(checkbox);

        const groupCell = newRow.insertCell();
        groupCell.textContent = student.ggg;

        const nameCell = newRow.insertCell();
        nameCell.innerHTML = student.first_name + " " + student.last_name;

        const genderCell = newRow.insertCell();
        genderCell.textContent = student.gender;

        const dobCell = newRow.insertCell();
        dobCell.innerHTML = new Date(student.birthday).toDateString();

        const statusCell = newRow.insertCell();
        const statusDiv = document.createElement("div");
        statusDiv.className = "status-active";
        statusCell.appendChild(statusDiv);

        const actionCell = newRow.insertCell();
        const editButton = document.createElement("button");
        editButton.className = "edit-row btn fa fa-edit";
        editButton.onclick = function () {
          studentIdToEdit = student.id;
          const a = document.getElementById("add-form-title");
          const b = document.getElementById("add-modal-create");
          a.innerHTML = "Edit Student";
          b.innerHTML = "Edit";
          addModal.style.display = "block";

          const fieldId = document.getElementById("add-form-field-id");
          fieldId.value = student.id;
          const fieldGroup = document.getElementById("add-form-field-group");
          for (let i = 0; i < fieldGroup.options.length; i++) {
            if (fieldGroup.options[i].text === student.group) {
              fieldGroup.selectedIndex = i;
              break;
            }
          }
          const fieldFirstName = document.getElementById("add-form-field-firstName");
          fieldFirstName.value = student.first_name;
          const fieldLastName = document.getElementById("add-form-field-lastName");
          fieldLastName.value = student.last_name;
          const fieldGender = document.getElementById("add-form-field-gender");
          for (let i = 0; i < fieldGender.options.length; i++) {
            if (fieldGender.options[i].text === student.gender) {
              fieldGender.selectedIndex = i;
              break;
            }
          }
          const fieldBirthday = document.getElementById("add-form-field-birthday");
          fieldBirthday.value = new Date(student.birthday).toISOString().slice(0,10);
          const name = fieldFirstName.value + " " + fieldLastName.value;
          const group = fieldGroup.options[fieldGroup.selectedIndex].textContent;
          const gender = fieldGender.options[fieldGender.selectedIndex].textContent;
          const birthday = fieldBirthday.value;
        };
        actionCell.appendChild(editButton);

        const deleteButton = document.createElement("button");
        deleteButton.className = "delete-row btn fa fa-remove";
        deleteButton.onclick = function() {
          warningModal.style.display = "block";
          studentIdToDelete = student.id;
        };
        actionCell.appendChild(deleteButton);
      });
    });
}

function clearTable() {
  const table = document.getElementById("table");
  let rowCount = table.rows.length;
  for (let i = rowCount - 1; i > 0; i--) {
    table.deleteRow(i);
  }
}

