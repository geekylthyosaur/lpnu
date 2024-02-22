<template>
  <header>
    <nav class="navbar navbar-expand-lg navbar-light bg-light">
      <div class="container">
        <!-- Logo on the left -->
        <a class="navbar-brand" href="#">
          <img src="path/to/logo.png" alt="Logo"/>
        </a>

        <!-- Login/Signup buttons or Notification/User icons on the right -->
        <div class="ml-auto">
          <ul class="navbar-nav">
            <!-- If user is not logged in -->
            <li v-if="!loggedIn" class="nav-item mr-1">
              <login-modal @loggedIn="setLoggedIn"/>
            </li>
            <li v-if="!loggedIn" class="nav-item ml-1">
              <signup-modal @loggedIn="setLoggedIn"/>
            </li>
            <!-- If user is logged in -->
            <div class="d-flex">
              <li @click="this.$emit('clicked')" v-if="loggedIn" class="nav-item dropdown">
                <a class="nav-link dropdown-toggle" href="#" role="button" data-toggle="dropdown" @mouseover="showNotificationsDropdown = true; showUserDropdown = false">
                  <!-- Notification icon with dot -->
                  <i :class="['fa', 'fa-bell', {'notification-dot': notifications.length}]"></i>
                </a>
                <div class="dropdown-menu dropdown-menu-right" v-bind:class="{ show: showNotificationsDropdown && notifications.length }"  @mouseleave="showNotificationsDropdown  = false">
                  <div v-for="(notification, index) in notifications" :key="index" class="dropdown-item">
                    <div class="row">
                      <div class="col-2">
                        <i class="fa fa-user"></i>
                      </div>
                      <div class="col-10">
                        <div>{{ notification }}</div>
                      </div>
                    </div>
                  </div>
                </div>
              </li>
              <li v-if="loggedIn" class="nav-item dropdown">
                <a class="nav-link dropdown-toggle col-1" href="#" role="button" @mouseover="showUserDropdown = true; showNotificationsDropdown = false">
                  <!-- User icon -->
                  <i class="fa fa-user"></i>
                </a>
                <div class="dropdown-menu dropdown-menu-right" v-bind:class="{ show: showUserDropdown }" @mouseleave="showUserDropdown = false">
                  <a class="dropdown-item" href="#">{{ username }}</a>
                  <a class="dropdown-item" href="#" @click="unsetLoggedIn">Logout</a>
                </div>
              </li>
            </div>
          </ul>
        </div>
      </div>
    </nav>
  </header>
</template>

<script>
  import LoginModal from './LoginModal.vue';
  import SignupModal from './SignupModal.vue';
  import io from 'socket.io-client'

  export default {
    name: 'SiteHeader',
    created() {
      this.socket = io('http://127.0.0.1:3080');
      const authToken = localStorage.getItem('token');
      const username = localStorage.getItem('username');
      if (authToken && username) {
        this.username = username;
        this.loggedIn = true;
        localStorage.setItem('token', `Bearer ${authToken}`);
        localStorage.setItem('username', `${username}`);
        setInterval(() => {
          this.socket.emit('getUnreadRooms', username);
        }, 1000);
        this.socket.on('unreadRooms', (unreadRooms) => {
          this.notifications = unreadRooms.map(room => room.name);
        });
      }
    },
    components: {
      'login-modal': LoginModal,
      'signup-modal': SignupModal,
    },
    data() {
      return {
        loggedIn: false,
        socket: null,
        username: '',
        showUserDropdown: false,
        showNotificationsDropdown: false,
        notifications: [],
      };
    },
    methods: {
      setLoggedIn(username, authToken) {
        this.username = username;
        this.loggedIn = true;
        localStorage.setItem('token', `Bearer ${authToken}`);
        localStorage.setItem('username', `${username}`);
      },
      unsetLoggedIn() {
        this.username = '';
        this.loggedIn = false;
        localStorage.clear();
      },
    },
  }
</script>

<style scoped>
.notification-dot {
  position: relative;
}

.notification-dot::after {
  content: '';
  position: absolute;
  top: -5px;
  right: -5px;
  width: 10px;
  height: 10px;
  background-color: red;
  border-radius: 50%;
  animation: blinking 1s infinite;
}

.dropdown-menu.show {
  display: block;
}

.dropdown-menu {
  display: none;
}
    
@keyframes blinking {
  0% {
    opacity: 0.5;
  }
  50% {
    opacity: 1;
  }
  100% {
    opacity: 0.5;
  }
}
</style>

