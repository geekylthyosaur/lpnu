<template>  
  <div class="container-fluid">
    <div class="row">
      <site-header loggedIn/>
    </div>
    <div class="row">
      <div class="col-md-3 sidebar">
        <sidebar/>
      </div>
      <div class="col-md-9">
        <students-table/>
      </div>
    </div>
  </div>
</template>

<script>
import SiteHeader from './components/Header.vue'
import StudentsTable from './components/StudentsTable.vue'
import SideBar from './components/Sidebar.vue'

export default {
  name: 'App',
  components: {
    'site-header': SiteHeader,
    'students-table': StudentsTable,
    'sidebar': SideBar,
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
}
</style>
