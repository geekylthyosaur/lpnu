<template>
  <div>
    <h2 style="margin-left: -1300px">Stops:</h2>
    <table v-if="data.length" class="data" style="width: 700px;">
      <tr v-for="item in data" :key="item">
        <td>{{ item }}</td>
      </tr>
    </table>
  </div>
</template>

<script>
import axios from "axios";

export default {
  data() {
    return {
      data: [],
    };
  },
  beforeMount() {
    this.fetchData();
  },
  methods: {
    fetchData() {
      setTimeout(() => {
     const vehicle_id = localStorage.getItem("vehicleId");
      const url = `http://localhost:8080/stops?vehicle_id=${vehicle_id}`;
      axios.get(url)
        .then(response => {
          this.data = response.data || [];
          this.isLoading = false;
        })
        .catch(error => {
          console.error("Error fetching data:", error);
          this.isLoading = false;
        }); }, 50);
      
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
