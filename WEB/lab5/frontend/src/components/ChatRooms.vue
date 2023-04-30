<template>
  <div class="container my-3 p-3 border rounded shadow-sm">
    <h3 class="text-center mb-4">My Chat Rooms</h3>
    <ul class="list-group row">
      <a v-for="room in rooms" :key="room._id" @click="$emit('roomSelected', room._id)">
        <li class="list-group-item py-3 mb-2">
          {{ room.name }}
          <button @click="deleteRoom(room._id)" class="btn btn-outline-danger btn-sm float-right">Leave</button>
        </li>
      </a>
    </ul>
    <chat-room-create-modal @roomCreated="fetchAvailableRooms" class="d-flex align-items-center justify-content-center"/>
  </div>
</template>

<script>
  import ChatRoomCreateModal from './ChatRoomCreateModal.vue'
  import axios from 'axios'

  const currentUsername = localStorage.getItem('username');

  export default {
    name: 'ChatRooms',
    data() {
      return {
        rooms: [],
      };
    },
    components: {
      'chat-room-create-modal': ChatRoomCreateModal,
    },
    mounted() {
      this.fetchAvailableRooms();
    },
    methods: {
      deleteRoom(roomId) {
        this.rooms = this.rooms.filter(room => room._id !== roomId);
        axios.delete(`http://127.0.0.1:3000/rooms/${roomId}/${currentUsername}`)
          .then(() => {
          })
          .catch(error => {
            // Handle error
            console.error(error);
          });
      },
      fetchAvailableRooms() {
        axios.get(`http://127.0.0.1:3000/rooms/all/${currentUsername}`)
          .then(response => {
            this.rooms = response.data;
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
</style>

