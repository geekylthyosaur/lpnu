<template>
  <div class="list-group text-center">
    <router-link to="/dashboard" class="list-group-item" v-bind:class="{ active: selectedTab === 'dashboard'}">
      Dashboard
    </router-link>
    <router-link to="/students" class="list-group-item" v-bind:class="{ active: selectedTab === 'students'}">
      Students
    </router-link>
    <router-link to="/tasks" class="list-group-item" v-bind:class="{ active: selectedTab === 'tasks'}">
      Tasks
    </router-link>
  </div>
</template>

<script>
  export default {
    name: 'SideBar',
    props: {
      selectedTab: {
        type: String,
        default: 'students',
      },
    },
  };
</script>

<style scoped>
.list-group {
  margin-bottom: 0;
}

.list-group-item {
  border: none;
  border-radius: 5;
  font-weight: bold;
}

.list-group-item.active {
  background-color: #007bff;
  color: #fff;
}

.list-group-item:hover {
  background-color: #007bff;
  color: #fff;
}
</style>
