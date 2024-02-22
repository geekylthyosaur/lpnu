<template>
  <div>
    <button type="button" class="btn btn-secondary" @click="openModal">Login</button>

    <div class="modal fade" tabindex="-1" role="dialog" v-bind:class="{ 'show': showModal }">
      <div class="modal-dialog" role="document">
        <div class="modal-content">
          <div class="modal-header">
            <h5 class="modal-title">Login</h5>
            <button type="button" class="close" data-dismiss="modal" aria-label="Close" @click="closeModal">
              <span aria-hidden="true">&times;</span>
            </button>
          </div>
          <div class="modal-body">
            <form>
              <div class="form-group">
                <label for="username">Username</label>
                <input type="text" class="form-control" id="username" v-model="username" v-bind:class="{ 'is-invalid': authFailed }">
              </div>
              <div class="form-group">
                <label for="password">Password</label>
                <input type="password" class="form-control" id="password" v-model="password" v-bind:class="{ 'is-invalid': authFailed }">
              </div>
            </form>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-secondary" data-dismiss="modal" @click="closeModal">Close</button>
            <button type="button" class="btn btn-primary" @click="login">Login</button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import axios from 'axios'

  export default {
    name: 'LoginModal',
    data() {
      return {
        username: '',
        password: '',
        showModal: false,
        authFailed: false,
      };
    },
    methods: {
      openModal() {
        this.showModal = true;
      },
      closeModal() {
        this.showModal = false;
      },
      login() {
        const user = {
          username: this.username,
          password: this.password,
        };
        axios.post('http://127.0.0.1:3000/login', user)
          .then(response => {
            this.$emit('loggedIn', this.username, response.data.token);
            this.authFailed = false;
            this.closeModal();
          })
          .catch(() => {
            this.authFailed = true;
            return;
          });
      }
    }
  };
</script>

<style scoped>
  .modal {
    display: none;
  }

  .modal.show {
    display: block;
  }
</style>
