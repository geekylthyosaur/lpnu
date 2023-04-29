<template>
  <div class="container">
    <div class="row">
      <div class="col-md-4">
        <chat-rooms @choosedRoom="chooseRoom"/>
      </div>
      <div class="col-md-8">
        <chat-room v-if="currentRoom !== ''"/>
      </div>
    </div>
  </div>
</template>

<script>
  import ChatRooms from './ChatRooms.vue'
  import ChatRoom from './ChatRoom.vue'
  import io from 'socket.io-client';

  export default {
    name: 'ChatClient',
    components: {
      'chat-rooms': ChatRooms,
      'chat-room': ChatRoom,
    },
    data() {
      return {
        socket: null,
        rooms: [],
        currentRoom: '',
        messages: [],
        messageText: '',
      };
    },
    mounted() {
      this.socket = io('http://localhost:3080');
      this.socket.on('rooms', (rooms) => {
        this.rooms = rooms;
        if (this.rooms.length > 0) {
          this.currentRoom = this.rooms[0];
          this.joinRoom(this.currentRoom);
        }
      });
      this.socket.on('message', (message) => {
        this.messages.push(message);
      });
    },
    methods: {
      joinRoom(room) {
        this.socket.emit('join', room);
        this.currentRoom = room;
        this.messages = [];
      },
      leaveRoom() {
        this.socket.emit('leave', this.currentRoom);
        this.currentRoom = '';
        this.messages = [];
      },
      sendMessage() {
        this.socket.emit('message', this.messageText);
        this.messageText = '';
      },
    },
  };
</script>

<style>
#messages {
  max-height: 300px;
  overflow-y: auto;
}
</style>

