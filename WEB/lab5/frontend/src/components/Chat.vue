<template>
  <div class="container">
    <div class="row">
      <div class="col-md-4">
        <chat-rooms @roomSelected="selectRoom"/>
      </div>
      <div class="col-md-8">
        <chat-room v-if="currentRoomId !== ''" v-bind:currentRoomId="currentRoomId"/>
      </div>
    </div>
  </div>
</template>

<script>
  import ChatRooms from './ChatRooms.vue'
  import ChatRoom from './ChatRoom.vue'

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
        currentRoomId: '',
        messages: [],
        messageText: '',
      };
    },
    methods: {
      selectRoom(roomid) {
        this.currentRoomId = roomid;
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

