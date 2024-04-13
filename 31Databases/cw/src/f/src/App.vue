<template>
  <div v-if="authenticated && role === 'passenger'">
    <button @click="logout" class="logout-button">Logout</button>
    <RouteWithStops />
    <ArrivalIn />
  </div>
  <div v-if="authenticated && role === 'driver'">
    <button @click="logout" class="logout-button">Logout</button>
    <InsertMaintenance/>
  </div>
  <div v-if="authenticated && role === 'manager'">
    <button @click="logout" class="logout-button">Logout</button>
    <ExportData :table="'driver'"/>
    <br>
    <ExportData :table="'maintenance'"/>
    <br>
    <ExportData :table="'vehicle'"/>
    <br>
    <ExportData :table="'schedule'"/>
    <br>
    <ExportData :table="'route'"/>
    <br>
    <ExportData :table="'stop'"/>
  </div>
  <div v-if="!authenticated">
    <div class="login-form">
      <h2>Please login</h2>
      <input type="text" v-model="username" placeholder="Username" class="input-field">
      <input type="password" v-model="password" placeholder="Password" class="input-field">
      <button @click="login" class="login-button">Login</button>
      <p v-if="loginError" class="error-message">{{ loginError }}</p>
    </div>
  </div>
</template>

<script>
import axios from 'axios';
import RouteWithStops from './components/RouteWithStops.vue'
import ArrivalIn from './components/ArrivalIn.vue'
import InsertMaintenance from './components/InsertMaintenance.vue'
import ExportData from './components/ExportData.vue'

export default {
  name: 'App',
  components: {
    RouteWithStops,
    ArrivalIn,
    InsertMaintenance,
    ExportData,
  },
  data() {
    return {
      role: '',
      username: localStorage.getItem('username') || '',
      password: '',
      authenticated: localStorage.getItem('username') !== null,
      loginError: ''
    };
  },
  beforeMount() {
    this.role = this.username;
    this.setAuthorizationHeader();
  },
  methods: {
    login() {
      if (this.username === 'passenger' && this.password === 'password') {
        this.role = 'passenger';
        this.authenticated = true;
        this.loginError = '';
        localStorage.setItem('username', this.username);
        this.setAuthorizationHeader();
      } else if (this.username === 'driver' && this.password === 'password') {
        this.role = 'driver';
        this.authenticated = true;
        this.loginError = '';
        localStorage.setItem('username', this.username);
        this.setAuthorizationHeader();
      } else if (this.username === 'manager' && this.password === 'password') {
        this.role = 'manager';
        this.authenticated = true;
        this.loginError = '';
        localStorage.setItem('username', this.username);
        this.setAuthorizationHeader();
      } else {
        this.authenticated = false;
        this.loginError = 'Invalid username or password';
        localStorage.removeItem('username');
        this.removeAuthorizationHeader();
      }
    },
    logout() {
      this.username = '';
      this.password = '';
      this.authenticated = false;
      localStorage.removeItem('username');
      this.removeAuthorizationHeader();
    },
    setAuthorizationHeader() {
      axios.defaults.headers.common['Authorization'] = this.username;
    },
    removeAuthorizationHeader() {
      delete axios.defaults.headers.common['Authorization'];
    }
  }
}
</script>

<style>
#app {
  font-family: Arial, sans-serif;
  text-align: center;
  margin-top: 60px;
}

.login-form {
  max-width: 300px;
  margin: 0 auto;
}

.input-field {
  width: 100%;
  padding: 10px;
  margin-bottom: 10px;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
}

.login-button {
  width: 100%;
  padding: 10px;
  background-color: #4CAF50;
  color: white;
  border: none;
  border-radius: 4px;
  cursor: pointer;
}

.login-button:hover {
  background-color: #45a049;
}

.error-message {
  color: red;
  font-size: 14px;
  margin-top: 5px;
}
.logout-button {
  width: 5%;
  padding: 10px;
  background-color: #f44336; /* Red color */
  color: white;
  border: none;
  border-radius: 4px;
  cursor: pointer;
  margin-bottom: 10px; /* Add some spacing below the logout button */
}

.logout-button:hover {
  background-color: #d32f2f; /* Darker shade of red on hover */
}

</style>

