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

function deleteRow(button) {
  warningModal.style.display = "block";

  const warningDeleteBtn = document.getElementById("warning-modal-delete");
  warningDeleteBtn.addEventListener("click", () => {
    const row = button.closest("tr");
    row.parentNode.removeChild(row);
    warningModal.style.display = "none";
  })
}



// Add row to table && add modal
const addButton = document.getElementById("add-row");
const addModal = document.getElementById("add-modal-wrapper");
const modalCloseBtn = document.getElementById("add-modal-close");
const modalCreateBtn = document.getElementById("add-modal-create");
const addForm = document.getElementById("add-form");

addButton.addEventListener("click", () => {
  addModal.style.display = "block";
  addStudent();
})

modalCloseBtn.addEventListener('click', () => {
  addModal.style.display = "none";
});

function addStudent() {
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
  modalCreateBtn.addEventListener('click', () => {
    addModal.style.display = "none";
    addForm.reset();

    const table = document.getElementById("table");
    const newRow = table.insertRow();
    const checkboxCell = newRow.insertCell();
    const checkbox = document.createElement("input");
    checkbox.type = "checkbox";
    checkbox.className = "check";
    checkboxCell.appendChild(checkbox);

    const groupCell = newRow.insertCell();
    groupCell.textContent = group;

    const nameCell = newRow.insertCell();
    nameCell.innerHTML = name;

    const genderCell = newRow.insertCell();
    genderCell.textContent = gender;

    const dobCell = newRow.insertCell();
    dobCell.innerHTML = birthday;

    const statusCell = newRow.insertCell();
    const statusDiv = document.createElement("div");
    statusDiv.className = "status-active";
    statusCell.appendChild(statusDiv);

    const actionCell = newRow.insertCell();
    const editButton = document.createElement("button");
    editButton.className = "edit-row btn fa fa-edit";
    editButton.onclick = function () {
      editRow(this);
    };
    actionCell.appendChild(editButton);

    const deleteButton = document.createElement("button");
    deleteButton.className = "delete-row btn fa fa-remove";
    deleteButton.onclick = function () {
      deleteRow(this);
    };
    actionCell.appendChild(deleteButton);
  });
  const json = {
    "id": id,
    "group": group,
    "name": name,
    "gender": gender,
    "birthday": birthday,
  };
  return JSON.stringify(json);
}

window.onclick = function (event) {
  if (event.target === addModal) {
    addModal.style.display = "none";
  }
};



// Edit row of table
function editRow(button) {
  alert("Edit button clicked!");
}



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
