<template>
  <div>
    <h1>Find time to arrival</h1>
    <div>
      <div class="search-container">
        <label for="fromStopID">From Stop:</label>
        <SearchStop id="fromStopID" @stop-selected="fromStopSelected" />
      </div>
      <div class="search-container">
        <label for="toStopID">To Stop:</label>
        <SearchStop id="toStopID" @stop-selected="toStopSelected" />
      </div>
      <div class="search-container">
        <label for="routeID">Route:</label>
        <SearchRoute id="routeID" @route-selected="routeSelected" />
      </div>
      <button @click="fetchRoutes" class="apply-filters-btn">Search</button>
    </div>
    <ul v-if="routes.length" class="routes-list">
      <li v-for="(route, index) in routes" :key="index">
        <h2>{{ route.route_name }}</h2>
        <p>From: {{ route.from_stop_name }}</p>
        <p>To: {{ route.to_stop_name }}</p>
        <p>Arrival in: {{ formatArrivalTime(route.arr_in) }}</p>
      </li>
    </ul>
    <p v-else>Not found.</p>
  </div>
</template>

<script>
import SearchStop from './SearchStop.vue';
import SearchRoute from './SearchRoute.vue';

export default {
  components: {
    SearchStop,
    SearchRoute,
  },
  data() {
    return {
      routes: [],
      fromStopID: '',
      toStopID: '',
      routeID: '',
    };
  },
  methods: {
    formatArrivalTime(time) {
      console.log(typeof time);
      if (!time) return '';
      const hours = parseInt(time.substring(0, 2));
      const minutes = parseInt(time.substring(3, 5));
      return `${hours} minutes, ${minutes} seconds`;
    },
    fromStopSelected(stop) {
      this.fromStopID = stop.id;
    },
    toStopSelected(stop) {
      this.toStopID = stop.id;
    },
    routeSelected(route) {
      this.routeID = route.id;
    },
    fetchRoutes() {
      const url = new URL('http://localhost:8080/arrival_with_stops_in');
      const params = { 
        from_stop_id: this.fromStopID, 
        to_stop_id: this.toStopID,
        route_id: this.routeID,
      };
      url.search = new URLSearchParams(params).toString();
      
      fetch(url)
        .then(response => response.json())
        .then(data => {
          console.log(data);
          this.routes = data || [];
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

