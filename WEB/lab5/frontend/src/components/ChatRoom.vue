<template>
  <div class="container">
    <h3>{{ currentRoom.name }}</h3>
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
  export default {
    name: 'ChatRoom',
    mounted() {
      // get messages from api
    },
    data() {
      return {
        currentUser: localStorage.getItem('username'),
        currentRoom: {
          id: 1,
          name: 'Chat Room 1',
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
        this.currentRoom.messages.push(message);
        this.newMessage = '';
      }
    }
  };
</script>

<style scoped>
</style>

