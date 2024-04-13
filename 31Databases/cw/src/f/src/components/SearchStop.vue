<template>
  <div class="search-container">
    <input type="text" v-model="searchTerm" @input="searchStops" placeholder="Search for a stop" class="search-input">
    <div v-if="showResults" class="search-results">
      <div v-for="stop in stops" :key="stop.id" @click="selectStop(stop.id, stop.name)">
        {{ stop.name }}
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
      stops: [],
      showResults: false
    };
  },
  watch: {
    searchTerm(newVal) {
      if (newVal === '') {
        this.$emit('stop-selected', { id: '', name: '' });
      }
    }
  },
  methods: {
    searchStops() {
      if (this.searchTerm.length > 0) {
        axios.get(`http://localhost:8080/search_stop?name=${this.searchTerm}`)
          .then(response => {
            this.stops = response.data;
            this.showResults = true;
          })
          .catch(error => {
            console.error('Error searching for stops:', error);
          });
      } else {
        this.stops = [];
        this.showResults = false;
      }
    },
    selectStop(stopId, stopName) {
      this.searchTerm = stopName;
      this.$emit('stop-selected', { id: stopId, name: stopName });
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

