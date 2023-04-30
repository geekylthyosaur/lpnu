<template>
  <div class="container">
    <div class="row">
      <div class="col-md-5 ml-5">
        <h3>{{ currentRoom.name }}</h3>
      </div>
      <div class="col-md-5 mr-5">
        <button @click="this.$emit('closeChat')" type="button" class="close">
          <span>&times;</span>
        </button>
      </div>
    </div>
    <ul class="list-group">
      <li v-for="message in currentRoom.messages" :key="message.id" class="list-group-item">
        <strong>{{ message.author }}:</strong> {{ message.content }}
      </li>
    </ul>
    <div class="input-group mt-3">
      <input v-model="newMessage" type="text" class="form-control" placeholder="Type your message...">
      <div class="input-group-append">
        <button @click="sendMessage" class="btn btn-primary">Send</button>
      </div>
    </div>
  </div>
</template>

<script>
  import axios from 'axios'
  import io from 'socket.io-client'

  export default {
    name: 'ChatRoom',
    mounted() {
      axios.get(`http://127.0.0.1:3000/rooms/${this.currentRoomId}`)
        .then(response => {
          console.log(response);
          this.currentRoom = response.data;
        })
        .catch(error => {
          // Handle error
          console.error(error);
        });

      this.socket = io('http://127.0.0.1:3080');
      this.socket.emit('getOldMessages', this.currentRoomId);
      this.socket.on('oldMessages', oldMessages => {
        this.currentRoom.messages = oldMessages;
      });
    },
    props: {
      currentRoomId: String,
    },
    data() {
      return {
        currentUser: localStorage.getItem('username'),
        currentRoom: {
          id: '',
          name: '',
          messages: [],
        },
        newMessage: ''
      };
    },
    methods: {
      sendMessage() {
        if (this.newMessage.trim() === '') {
          return;
        }
        const message = {
          id: this.currentRoom.messages.length + 1,
          author: this.currentUser,
          content: this.newMessage.trim()
        };
        this.socket.emit('newMessage', this.currentRoomId, this.currentUser, this.newMessage);
        this.currentRoom.messages.push(message);
        this.newMessage = '';
      },
    }
  };
</script>

<style scoped>
</style>

