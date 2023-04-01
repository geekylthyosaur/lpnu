let students = []
let globalStudentId = 1;
let studentIdToDelete = 0;
let studentIdToEdit = 0;
// Checkboxes
const checkAll = document.getElementById("check-all");

checkAll.addEventListener("click", () => {
  const checkboxes = document.querySelectorAll(".check");
  checkboxes.forEach((checkbox) => {
    checkbox.checked = checkAll.checked;
  });
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
  const i = students.findIndex(s => s.id === studentIdToDelete);
  students.splice(i, 1);
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
  addModal.style.display = "none";
});

function addStudent() {
  const fieldId = document.getElementById("add-form-field-id");
  const fieldGroup = document.getElementById("add-form-field-group");
  const fieldFirstName = document.getElementById("add-form-field-firstName");
  const fieldLastName = document.getElementById("add-form-field-lastName");
  const fieldGender = document.getElementById("add-form-field-gender");
  const fieldBirthday = document.getElementById("add-form-field-birthday");
  const id = globalStudentId++;
  fieldId.value = id;
  const name = fieldFirstName.value + " " + fieldLastName.value;
  const group = fieldGroup.options[fieldGroup.selectedIndex].textContent;
  const gender = fieldGender.options[fieldGender.selectedIndex].textContent;
  const birthday = fieldBirthday.value;
  addModal.style.display = "none";

  const student = {
    "id": id,
    "group": group,
    "name": name,
    "gender": gender,
    "birthday": birthday,
    "status": 1,
  };

  students.push(student);

  clearTable();
  drawTable();
  addForm.reset();
  console.log(JSON.stringify(student));
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
  const name = fieldFirstName.value + " " + fieldLastName.value;
  const group = fieldGroup.options[fieldGroup.selectedIndex].textContent;
  const gender = fieldGender.options[fieldGender.selectedIndex].textContent;
  const birthday = fieldBirthday.value;
  addModal.style.display = "none";

  const student = {
    "id": id,
    "group": group,
    "name": name,
    "gender": gender,
    "birthday": birthday,
    "status": 1,
  };

  students[i] = student;

  clearTable();
  drawTable();
  addForm.reset();
  console.log(JSON.stringify(student));
  warningModal.style.display = "none";
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
  students.forEach((student) => {
    const newRow = table.insertRow();
    newRow.id = student.id;
    const checkboxCell = newRow.insertCell();
    const checkbox = document.createElement("input");
    checkbox.type = "checkbox";
    checkbox.className = "check";
    checkboxCell.appendChild(checkbox);

    const groupCell = newRow.insertCell();
    groupCell.textContent = student.group;

    const nameCell = newRow.insertCell();
    nameCell.innerHTML = student.name;

    const genderCell = newRow.insertCell();
    genderCell.textContent = student.gender;

    const dobCell = newRow.insertCell();
    dobCell.innerHTML = student.birthday;

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
      fieldFirstName.value = student.name.split(" ")[0];
      const fieldLastName = document.getElementById("add-form-field-lastName");
      fieldLastName.value = student.name.split(" ")[1];
      const fieldGender = document.getElementById("add-form-field-gender");
      for (let i = 0; i < fieldGender.options.length; i++) {
        if (fieldGender.options[i].text === student.gender) {
          fieldGender.selectedIndex = i;
          break;
        }
      }
      const fieldBirthday = document.getElementById("add-form-field-birthday");
      fieldBirthday.value = student.birthday;
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
}

function clearTable() {
  const table = document.getElementById("table");
  let rowCount = table.rows.length;
  for (let i = rowCount - 1; i > 0; i--) {
    table.deleteRow(i);
  }
}
