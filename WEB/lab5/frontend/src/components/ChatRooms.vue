<template>
  <div class="container">
    <h3>My Chat Rooms</h3>
    <ul class="list-group row">
      <li v-for="room in rooms" :key="room.id" class="list-group-item">
        <a :href="`/chat/${room.id}`">{{ room.name }}</a>
        <button @click="removeRoom(room.id)" class="btn btn-danger btn-sm float-right">Exit</button>
      </li>
    </ul>
    <chat-room-create-modal class="row mt-2"/>
  </div>
</template>

<script>
  import ChatRoomCreateModal from './ChatRoomCreateModal.vue'

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
    methods: {
      removeRoom(roomId) {
        this.rooms = this.rooms.filter(room => room.id !== roomId);
      }
    }
  };
</script>

<style scoped>
</style>

