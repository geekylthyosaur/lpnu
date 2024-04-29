<template>
  <div class="maintenance-form">
    <form @submit.prevent="submitForm">
      <div class="form-group">
        <label for="description">Description:</label>
        <textarea id="description" v-model="formData.description" required></textarea>
      </div>
      <div class="form-group">
        <label for="cost">Cost:</label>
        <input type="number" id="cost" v-model="formData.cost" required>
      </div>
      <button type="submit">Submit</button>
    </form>

  <div v-if="isSuccess">
    Success
  </div>
  </div>
</template>

<script>
import axios from 'axios';

export default {
  data() {
    return {
      formData: {
        vehicle_id: '',
        driver_id: parseInt(localStorage.getItem("driverId"), 10),
        description: '',
        cost: null
      },
        isSuccess: false,
    };
  },
  methods: {
    submitForm() {
      this.formData.vehicle_id = localStorage.getItem("vehicleId");
      axios.post('http://localhost:8080/insert_maintenance', this.formData)
        .then(response => {
          console.log('Maintenance data submitted successfully:', response.data);
          this.isSuccess = true;
          this.resetForm();
        })
        .catch(error => {
          console.error('Error submitting maintenance data:', error);
        });
    },
    resetForm() {
      this.formData.vehicle_id = '';
      this.formData.driver_id = null;
      this.formData.description = '';
      this.formData.cost = null;
    }
  }
};
</script>

<style scoped>
.maintenance-form {
  max-width: 400px;
  margin: auto;
}

.form-group {
  margin-bottom: 15px;
}

label {
  display: block;
}

input[type="text"],
input[type="number"],
textarea {
  width: 100%;
  padding: 8px;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
}

button[type="submit"] {
  background-color: #4CAF50;
  color: white;
  padding: 10px 20px;
  border: none;
  border-radius: 4px;
  cursor: pointer;
}

button[type="submit"]:hover {
  background-color: #45a049;
}
</style>

