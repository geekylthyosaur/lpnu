<template>
  <div class="container">
    <h3>My Chat Rooms</h3>
    <ul class="list-group row">
      <li v-for="room in rooms" :key="room._id" class="list-group-item">
        <a @click="this.$emit('roomSelected', room._id)">{{ room.name }}</a>
        <button @click="deleteRoom(room._id)" class="btn btn-danger btn-sm float-right">Exit</button>
      </li>
    </ul>
    <chat-room-create-modal @roomCreated="fetchAvailableRooms" class="row mt-2"/>
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

