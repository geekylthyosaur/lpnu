<template>
  <div>
    <button type="button" class="btn btn-primary" @click="openModal">Sign Up</button>

    <div class="modal fade" tabindex="-1" role="dialog" v-bind:class="{ 'show': showModal }">
      <div class="modal-dialog" role="document">
        <div class="modal-content">
          <div class="modal-header">
            <h5 class="modal-title">Sign Up</h5>
            <button type="button" class="close" data-dismiss="modal" aria-label="Close" @click="closeModal">
              <span aria-hidden="true">&times;</span>
            </button>
          </div>
          <div class="modal-body">
            <form>
              <div class="form-group">
                <label for="username">Username</label>
                <input type="text" class="form-control" id="username" v-model="username">
              </div>
              <div class="form-group">
                <label for="password">Password</label>
                <input type="password" class="form-control" id="password" v-model="password">
              </div>
              <div class="form-group">
                <label for="rpassword">Repeat Password</label>
                <input type="password" class="form-control" id="rpassword" v-model="rpassword">
              </div>
            </form>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-secondary" data-dismiss="modal" @click="closeModal">Close</button>
            <button type="button" class="btn btn-primary" @click="signup">Sign Up</button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import axios from 'axios'

  export default {
    name: 'SignupModal',
    data() {
      return {
        username: '',
        password: '',
        rpassword: '',
        showModal: false
      };
    },
    methods: {
      openModal() {
        this.showModal = true;
      },
      closeModal() {
        this.showModal = false;
      },
      signup() {
        if (this.password !== this.rpassword) {
          alert("Password doesn't match!");
          return;
        }
        const user = {
          username: this.username,
          password: this.password,
        };
        axios.post('http://127.0.0.1:3000/signup', user)
          .then(() => {
            this.$emit('loggedIn', this.username);
          })
          .catch(error => {
            console.log(error);
          });
        this.closeModal();
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
