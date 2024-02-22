<template>
  <div class="container">
    <button @click="openModal" type="button" class="btn btn-primary">
      Create Chat Room
    </button>
    <div class="modal fade" tabindex="-1" role="dialog" v-bind:class="{ 'show': showModal }">
      <div class="modal-dialog modal-dialog-centered" role="document">
        <div class="modal-content">
          <div class="modal-header">
            <h5 class="modal-title" id="createRoomModalLabel">Create Chat Room</h5>
            <button @click="closeModal" type="button" class="close" aria-label="Close">
              <span aria-hidden="true">&times;</span>
            </button>
          </div>
          <div class="modal-body">
            <div class="form-group">
              <label for="roomName">Room Name:</label>
              <input v-model="newRoomName" type="text" class="form-control" id="roomName" placeholder="Enter room name...">
            </div>
            <div class="form-group">
              <label for="userList">Select users:</label>
              <select v-model="selectedUsers" multiple class="form-control" id="userList">
                <option v-for="user in userList" :key="user.id" :value="user">{{ user.username }}</option>
              </select>
            </div>
          </div>
          <div class="modal-footer">
            <button @click="closeModal" type="button" class="btn btn-secondary">Close</button>
            <button @click="createRoom" type="button" class="btn btn-primary">Create Room</button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import axios from 'axios'

  const currentUsername = localStorage.getItem('username');
  
  export default {
    data() {
      return {
        showModal: false,
        userList: [],
        newRoomName: '',
        selectedUsers: []
      };
    },
    mounted() {
      axios.get('http://127.0.0.1:3000/all')
        .then(response => {
          this.userList = response.data.filter(user => user.username !== currentUsername);
        })
        .catch(error => {
          console.error(error);
        });
    },
    methods: {
      openModal() {
        this.showModal = true
        document.body.classList.add('modal-open')
      },
      closeModal() {
        this.showModal = false
        document.body.classList.remove('modal-open')
      },
      createRoom() {
        axios.post('http://127.0.0.1:3000/rooms', {
          name: this.newRoomName,
          users: this.selectedUsers.map(user => user.username).concat(currentUsername),
        })
          .then(() => {
            this.closeModal();
            this.$emit('roomCreated', this.newRoomName);
          })
          .catch(error => {
            // Handle error
            console.error(error);
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
