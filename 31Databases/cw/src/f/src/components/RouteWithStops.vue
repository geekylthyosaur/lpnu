<template>
  <div>
    <h1>Search for routes</h1>
    <div>
      <div class="container">
        <SearchStop :label="'From stop:'" @stop-selected="fromStopSelected" />
      </div>
      <div class="container">
        <SearchStop :label="'To stop:'" @stop-selected="toStopSelected" />
      </div>
      <button @click="fetchRoutes" :disabled="!fromStopID && !toStopID" class="search-button">Search</button>
    </div>
    <table v-if="routes.length" class="routes">
      <tr>
        <td>Route name</td>
        <td>From stop name</td>
        <td>To stop name</td>
      </tr>
      <tr v-for="(route, index) in routes" :key="index">
        <td>{{ route.route_name }}</td>
        <td>{{ route.from_stop_name }}</td>
        <td>{{ route.to_stop_name }}</td>
      </tr>
    </table>
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
.container {
  margin-bottom: 20px;
}

.search-button {
  background-color: #4CAF50;
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

.search-button:disabled {
  background-color: #bbb;
}

label {
  display: block;
  font-weight: bold;
  margin-bottom: 5px;
}

.search-button {
  background-color: #4caf50;
  color: white;
  padding: 10px 20px;
  border: none;
  border-radius: 5px;
  cursor: pointer;
  font-size: 16px;
}

.search-button:hover {
  background-color: #45a049;
}

.routes {
  width: 100%;
  border-collapse: collapse;
}

.routes th,
.routes td {
  padding: 8px;
  border: 1px solid #ddd;
  text-align: left;
}

.routes th {
  background-color: #f2f2f2;
  font-weight: bold;
}

.routes tr:nth-child(even) {
  background-color: #f2f2f2;
}
</style>

