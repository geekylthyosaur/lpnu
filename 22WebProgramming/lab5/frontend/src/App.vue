<template>  
  <div class="container-fluid">
    <div class="row">
      <site-header @clicked="headerClick"/>
    </div>
    <div class="row">
      <div class="col-md-3 mt-3 sidebar">
        <sidebar v-if="!showChat && !showTasks" selectedTab="students" @clicked="sidebarClick"/>
        <sidebar v-if="!showChat && showTasks" selectedTab="tasks" @clicked="sidebarClick"/>
        <sidebar v-if="showChat" selectedTab="none" @clicked="sidebarClick"/>
      </div>
      <div v-if="!showChat && !showTasks" class="col-md-9">
        <students-table class="mt-3"/>
      </div>
      <div v-if="showChat" class="col-md-9">
        <chat class="mt-3"/>
      </div>
      <div v-if="showTasks" class="col-md-9">
        <tasks class="mt-3"/>
      </div>
    </div>
  </div>
</template>

<script>
import SiteHeader from './components/Header.vue'
import StudentsTable from './components/StudentsTable.vue'
import SideBar from './components/Sidebar.vue'
import ChatClient from './components/Chat.vue'
import TasksComponent from './components/Tasks.vue'

export default {
  name: 'App',
  data() {
    return {
      loggedIn: false,
      showChat: false,
      showTasks: false,
    };
  },
  components: {
    'site-header': SiteHeader,
    'students-table': StudentsTable,
    'sidebar': SideBar,
    'chat': ChatClient,
    'tasks': TasksComponent,
  },
  methods: {
    sidebarClick(tab) {
      if (tab === 'dashboard') {
        console.log('dashboard');
      } else if (tab === 'students') {
        this.showChat = false;
        this.showTasks = false;
      } else if (tab === 'tasks') {
        this.showChat = false;
        this.showTasks = true;
        console.log('tasks');
      }
    },
    headerClick() {
      this.showChat = true;
      this.showTasks = false;
    }
  },
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
}
</style>
