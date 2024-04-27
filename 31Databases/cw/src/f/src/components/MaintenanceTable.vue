<template>
  <div>
    <input type="text" v-model="searchTerm" id="input_search" @input="search" placeholder="Search" class="input-field">
    <ExportData :table="'maintenance'"/>
    <table v-if="data.length" class="data">
      <tr>
        <td>Id</td>
        <td>Vehicle Id</td>
        <td>Driver Id</td>
        <td>Description</td>
        <td>Timestamp</td>
        <td>Cost</td>
      </tr>
      <tr v-for="item in data" :key="item.id">
        <td>{{ item.id }}</td>
        <td>{{ item.vehicle_id }}</td>
        <td>{{ item.driver_id }}</td>
        <td>{{ item.description }}</td>
        <td>{{ item.time }}</td>
        <td>{{ item.cost }}</td>
      </tr>
    </table>
    <p v-if="!data.length && !isLoading">No records found.</p>
    <p v-if="isLoading">Loading...</p>
  </div>
</template>

<script>
import axios from "axios";
import ExportData from "./ExportData.vue";

export default {
  data() {
    return {
      data: [],
      isLoading: true,
      show: "default",
      searchTerm: '',
    };
  },
  watch: {
    searchTerm(val) {
      if (val === '') {
        this.fetchData();
      }
    }
  },
  components: {
    ExportData,
  },
  beforeMount() {
    this.fetchData();
  },
  methods: {
    search() {
      this.data = this.data.filter(item => item.description.includes(this.searchTerm) || (''+ item.time).includes(this.searchTerm));
    },
    fetchData() {
      const url = "http://localhost:8080/maintenance";
      axios.get(url)
        .then(response => {
          this.data = response.data || [];
          this.isLoading = false;
        })
        .catch(error => {
          console.error("Error fetching data:", error);
          this.isLoading = false;
        });
    },
  }
}
</script>

<style scoped>
.input-field {
  width: 30%;
  padding: 10px;
  margin-bottom: 10px;
  margin-left: 10px;
  margin-right: 10px;
  border: 1px solid #ccc;
  border-radius: 4px;
}

.data {
  width: 100%;
  border-collapse: collapse;
}

.data th,
.data td {
  padding: 8px;
  border: 1px solid #ddd;
  text-align: left;
}

.data th {
  background-color: #f2f2f2;
  font-weight: bold;
}

.data tr:nth-child(even) {
  background-color: #f2f2f2;
}

.add-button,
.edit-button,
.remove-button {
  width: 80px;
  padding: 5px 10px;
  margin-right: 5px;
  border: none;
  border-radius: 5px;
  cursor: pointer;
  transition: background-color 0.3s ease, color 0.3s ease;
}

.add-button,
.edit-button {
  background-color: dodgerblue;
  color: white;
}

.add-button:hover,
.edit-button:hover {
  background-color: royalblue;
}

.remove-button {
  background-color: tomato;
  color: white;
}

.remove-button:hover {
  background-color: red;
}

.add-button {
  margin-bottom: 30px;
}
</style>


