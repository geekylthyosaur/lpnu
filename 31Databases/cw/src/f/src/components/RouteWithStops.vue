<template>
  <div>
    <h1>Search for routes</h1>
    <div>
      <div class="search-container">
        <label for="fromStopID">From Stop:</label>
        <SearchStop id="fromStopID" @stop-selected="fromStopSelected" />
      </div>
      <div class="search-container">
        <label for="toStopID">To Stop:</label>
        <SearchStop id="toStopID" @stop-selected="toStopSelected" />
      </div>
      <button @click="fetchRoutes" :disabled="!fromStopID || !toStopID" class="apply-filters-btn">Search</button>
    </div>
    <ul v-if="routes.length" class="routes-list">
      <li v-for="(route, index) in routes" :key="index">
        <h2>{{ route.route_name }}</h2>
        <p>From: {{ route.from_stop_name }}</p>
        <p>To: {{ route.to_stop_name }}</p>
      </li>
    </ul>
    <p v-else>No routes found.</p>
  </div>
</template>

<script>
import axios from 'axios';
import SearchStop from './SearchStop.vue';

export default {
  components: {
    SearchStop,
  },
  data() {
    return {
      routes: [],
      fromStopID: '',
      toStopID: '',
    };
  },
  methods: {
    fromStopSelected(stop) {
      this.fromStopID = stop.id;
    },
    toStopSelected(stop) {
      this.toStopID = stop.id;
    },
    fetchRoutes() {
      const url = 'http://localhost:8080/route_with_stops';
      const params = { from_stop_id: this.fromStopID, to_stop_id: this.toStopID };

      axios.get(url, { params })
        .then(response => {
          this.routes = response.data || [];
        })
        .catch(error => {
          console.error('Error fetching routes:', error);
        });
    },
  },
};
</script>

<style scoped>
.search-container {
  margin-bottom: 20px;
}

.apply-filters-btn {
  background-color: #4CAF50; /* Green */
  border: none;
  color: white;
  padding: 10px 24px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  transition-duration: 0.4s;
  cursor: pointer;
  border-radius: 8px;
}

.apply-filters-btn:hover {
  background-color: #45a049;
}

.routes-list {
  list-style-type: none;
  padding: 0;
}

.routes-list li {
  margin-bottom: 20px;
  border: 1px solid #ddd;
  padding: 10px;
  border-radius: 8px;
}
</style>

