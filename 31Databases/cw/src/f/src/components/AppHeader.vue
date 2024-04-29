<template>
  <header class="header">
    <img src="@/assets/logo.png" alt="Logo" class="logo">
    <div v-if="role !== ''" style="background-color:  white; padding: 9px; border-radius: 10px;color: black; margin-left: 1600px">
      {{ role }}
    </div>
    <button v-if="authenticated" @click="logout" class="logout-button">Log Out</button>
    <button v-else @click="login" class="login-button">Log In</button>
  </header>

  <LoginDialog v-if="this.loginDialog" @success="loginDialogSuccess" @cancel="loginDialogCancel"/>
</template>

<script>
  import LoginDialog from "./LoginDialog.vue"
  export default {
    components: {
      LoginDialog,
    },
    props: {
      authenticated: {
        type: Boolean,
        required: true,
      }
    },
    data() {
      return {
        loginDialog: false,
        role: localStorage.getItem('username') || '',
      };
    },
    methods: {
      login() {
        this.loginDialog = true;
      },
      logout() {
        localStorage.clear();
        this.$emit("logout");
        this.role = localStorage.getItem('username') || '';
      },
      loginDialogSuccess(username) {
        this.loginDialog = false;
        this.$emit("login", username);
        this.role = localStorage.getItem('username') || '';
      },
      loginDialogCancel() {
        this.loginDialog = false;
        this.role = localStorage.getItem('username') || '';
      },
    },
  }
</script>

<style scoped>
  .header {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 60px;
    display: flex;
    justify-content: space-between;
    align-items: center;
    background-color: black;
    box-sizing: border-box;
    padding: 0 20px;
    z-index: 9990;
  }

  .logo {
    width: 50px;
  }

  .login-button {
    width: 100px;
    background-color: gray;
    color: white;
    border: none;
    padding: 10px 20px;
    border-radius: 5px;
    cursor: pointer;
  }

  .logout-button {
    width: 100px;
    background-color: red;
    color: white;
    border: none;
    padding: 10px 20px;
    border-radius: 5px;
    cursor: pointer;
  }
</style>


