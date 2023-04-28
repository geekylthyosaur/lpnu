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
            <li v-if="!loggedIn" class="nav-item">
              <router-link class="nav-link" to="/login" style="user-select: none;">Login</router-link>
            </li>
            <li v-if="!loggedIn" class="nav-item">
              <router-link class="nav-link" to="/signup" style="user-select: none;">Signup</router-link>
            </li>
            <!-- If user is logged in -->
            <li v-if="loggedIn" class="nav-item dropdown">
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
                      <b>{{ notification.sender }}</b>
                      <div>{{ notification.message }}</div>
                    </div>
                  </div>
                </div>
              </div>
            </li>
            <li v-if="loggedIn" class="nav-item dropdown">
              <a class="nav-link dropdown-toggle" href="#" role="button" @mouseover="showUserDropdown = true; showNotificationsDropdown = false">
                <!-- User icon -->
                <i class="fa fa-user"></i>
              </a>
              <div class="dropdown-menu dropdown-menu-right" v-bind:class="{ show: showUserDropdown }" @mouseleave="showUserDropdown = false">
                <a class="dropdown-item" href="#">Profile</a>
                <a class="dropdown-item" href="#">Logout</a>
              </div>
            </li>
          </ul>
        </div>
      </div>
    </nav>
  </header>
</template>

<script>
  export default {
    name: 'SiteHeader',
    props: {
      loggedIn: Boolean,
      notifications: {
        type: Array,
        default() {
          return [];
        },
      },
    },
    data() {
      return {
        showUserDropdown: false,
        showNotificationsDropdown: false,
      };
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

