<template>
  <div class="modal">
    <div class="modal-content">
      <h2>Please log in</h2>
      <input type="text" v-model="username" placeholder="Username" class="input-field">
      <input type="password" v-model="password" placeholder="Password" class="input-field">
      <button @click="login" class="login-button">Log In</button>
      <button @click="cancel" class="cancel-button">Cancel</button>
      <p v-if="error" class="error-message">{{ error }}</p>
    </div>
  </div>
</template>

<script>
  import axios from 'axios';
export default {
  data() {
    return {
      username: '',
      password: '',
      error: ''
    }
  },
  mounted() {
    window.addEventListener("keyup", (e) => {
      if (e.key === "Enter") {
        this.login();
      } else if (e.key === "Escape") {
        this.cancel();
      }
    });
  },
  beforeUnmount() {
    window.removeEventListener("keyup", (e) => {
      if (e.key === "Enter") {
        this.login();
      } else if (e.key === "Escape") {
        this.cancel();
      }
    });
  },
  methods: {
    login() {
      if (this.username === "manager" && this.password === "password") {
        localStorage.setItem("username", this.username);
        this.$emit("success", this.username);
      } else {
        this.error = "Invalid credentials. Please try again.";
      }

      const regex = /^driver(\d+)$/;
      if (regex.test(this.username) && this.password === "password") {
        const driverId = parseInt(this.username.match(regex)[1]);
        localStorage.setItem("username", "driver");
        localStorage.setItem("driverId", driverId);
        axios.defaults.headers.common['Authorization'] = "driver";
        axios.get(`http://localhost:8080/driver/id?id=${driverId}`)
          .then(response => {
            localStorage.setItem("vehicleId", response.data.vehicle_id.String);
          })
          .catch(error => {
            console.error('Error:', error);
          });
        this.$emit("success", "driver", driverId);
      } else {
        this.error = "Invalid credentials. Please try again.";
      }
    },
    cancel() {
      this.$emit("cancel");
    }
  }
}
</script>

<style scoped>
.modal {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.5);
  display: flex;
  justify-content: center;
  align-items: center;
  z-index: 9999;
}

.modal-content {
  background-color: white;
  padding: 20px;
  border-radius: 8px;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  text-align: center;
}

.input-field {
  width: 80%;
  padding: 10px;
  margin-bottom: 10px;
  border: 1px solid #ccc;
  border-radius: 4px;
}

.login-button,
.cancel-button {
  width: 40%;
  padding: 10px;
  margin: 10px;
  color: white;
  border: none;
  border-radius: 4px;
  cursor: pointer;
}

.login-button {
  background-color: dodgerblue;
}

.cancel-button {
  background-color: gray;
}

.login-button:hover {
  background-color: royalblue;
}

.cancel-button:hover {
  background-color: dimgray;
}

.error-message {
  color: red;
}
</style>

