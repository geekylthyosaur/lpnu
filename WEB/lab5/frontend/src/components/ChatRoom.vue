<template>
  <div class="container">
    <div class="row">
      <div class="col-md-5 ml-5">
        <h3>{{ currentRoom.name }}</h3>
      </div>
      <div class="col-md-5 text-md-right mt-3 mt-md-0">
        <button @click="closeChat" type="button" class="close">
          <span>&times;</span>
        </button>
      </div>
    </div>
    <ul class="list-group messages-container">
      <li v-for="message in currentRoom.messages" :key="message.id" class="list-group-item">
        <strong>{{ message.author }}:</strong> {{ message.content }}
      </li>
    </ul>
    <div class="input-group mt-3">
      <input @keydown.enter="sendMessage" v-model="newMessage" type="text" class="form-control" placeholder="Type your message...">
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
    created() {
      axios.get(`http://127.0.0.1:3000/rooms/${this.currentRoomId}`)
        .then(response => {
          this.currentRoom = response.data;
        })
        .catch(error => {
          console.error(error);
        });

      this.socket = io('http://127.0.0.1:3080');
      this.socket.emit('joinRoom', this.currentRoomId);
      this.socket.emit('getOldMessages', this.currentRoomId);
      this.socket.on('oldMessages', oldMessages => {
        this.currentRoom.messages = oldMessages;
      });
      this.socket.on('newMessage', (author, content) => {
        this.currentRoom.messages.push({author, content})
      });
      this.interval = setInterval(() => {
        this.socket.emit('setRoomAsRead', this.currentRoomId, this.currentUser);
      }, 1000);
    },
    beforeUnmount() {
      clearInterval(this.interval);
    },
    props: {
      currentRoomId: String,
    },
    data() {
      return {
        currentUser: localStorage.getItem('username'),
        interval: null,
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
        this.socket.emit('newMessage', this.currentRoomId, this.currentUser, this.newMessage);
        this.newMessage = '';
      },
      closeChat() {
        this.socket.emit('leaveRoom', this.currentRoomId);
        this.$emit('closeChat');
      }
    }
  };
</script>

<style scoped>
  .messages-container {
    height: 50vh;
    min-height: 100px;
    overflow: auto;
  }
</style>

