const form = document.getElementById("rental-form");
const licenseCheckbox = document.getElementById("license");
const driverInfo = document.getElementById("driver-info");

licenseCheckbox.addEventListener("change", function() {
  if (this.checked) {
    driverInfo.style.display = "none";
  } else {
    driverInfo.style.display = "block";
  }
});

form.addEventListener("submit", function(event) {
  event.preventDefault();

  if (validateForm()) {
    alert("Your car has been rented successfully!");
    this.reset();
  } else {
    alert("Please check correctness of marked fields.");
  }
});

function validateForm() {
  let valid = true;

  const requiredFields = ["name", "surname"];

  for (let i = 0; i < requiredFields.length; i++) {
    const field = document.getElementById(requiredFields[i]);
    if (!/^[a-zA-Z ]+$/.test(field.value.trim())) {
      valid = false;
      field.classList.add("invalid");
    } else {
      field.classList.remove("invalid");
    }
  }

  const today = new Date();
  const start = document.getElementById("start-date");
  const end = document.getElementById("end-date");
  const startDate = new Date(document.getElementById("start-date").value);
  const endDate = new Date(document.getElementById("end-date").value);

  if (startDate > endDate || startDate < today || endDate < today) {
    valid = false;
    start.classList.add("invalid");
    end.classList.add("invalid");
  } else {
    start.classList.remove("invalid");
    end.classList.remove("invalid");
  }

  return valid;
}

function cancel() {
  form.reset();
}
