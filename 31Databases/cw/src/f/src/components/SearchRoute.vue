<template>
  <div class="search-container">
    <input type="text" v-model="searchTerm" @input="searchRoutes" placeholder="Search for a route" class="search-input">
    <div v-if="showResults" class="search-results">
      <div v-for="route in routes" :key="route.id" @click="selectRoute(route.id, route.name)">
        {{ route.name }}
      </div>
    </div>
  </div>
</template>

<script>
import axios from 'axios';

export default {
  data() {
    return {
      searchTerm: '',
      routes: [],
      showResults: false
    };
  },
  methods: {
    searchRoutes() {
      if (this.searchTerm.length > 0) {
        axios.get(`http://localhost:8080/search_route?name=${this.searchTerm}`)
          .then(response => {
            this.routes = response.data;
            this.showResults = true;
          })
          .catch(error => {
            console.error('Error searching for routes:', error);
          });
      } else {
        this.routes = [];
        this.showResults = false;
      }
    },
    selectRoute(routeId, routeName) {
      this.searchTerm = routeName;
      this.$emit('route-selected', { id: routeId, name: routeName });
      this.showResults = false;
    },
  }
};
</script>

<style>
.search-container {
  position: relative;
}

.search-input {
  padding: 8px;
  border: 1px solid #ccc;
  border-radius: 4px;
  width: 50%;
}

.search-results {
  position: absolute;
  top: calc(100% + 4px);
  left: 25%;
  background-color: white;
  border: 1px solid #ccc;
  max-height: 200px;
  overflow-y: auto;
  width: 50%;
  z-index: 999;
}
.search-results div {
  padding: 5px;
  cursor: pointer;
}
</style>

