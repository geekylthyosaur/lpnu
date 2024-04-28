<template>
  <div>
    <input type="text" v-model="searchTerm" id="input_search" @input="search" placeholder="Search" class="input-field">
    <ExportData :table="'vehicle'"/>
    <button @click="show = 'add'" class="add-button">Add</button>
    <div v-if="show === 'add' || show === 'edit'">
      <input v-if="show === 'add'" type="text" id="input_license" placeholder="License" class="input-field">
      <input type="text" id="input_capacity" placeholder="Capacity" class="input-field">
      <input type="text" id="input_route_id" placeholder="Route Id" class="input-field">
      <br>
      <button v-if="show === 'add'" @click="addItem" class="add-button">Add</button>
      <button v-if="show === 'edit'" @click="confirmEditItem" class="add-button">Edit</button>
      <button @click="cancel" class="add-button">Cancel</button>
    </div>
    <table v-if="data.length" class="data">
      <tr>
        <td @click="sortByLicense">License</td>
        <td @click="sortByCapacity">Capacity</td>
        <td @click="sortByRouteId">Route Id</td>
        <td></td>
      </tr>
      <tr v-for="item in data" :key="item.license">
        <td>{{ item.license }}</td>
        <td>{{ item.capacity }}</td>
        <td>{{ item.route_id.Valid ? item.route_id.Int64 : '' }}</td>
        <td style="text-align: center; width: 200px">
          <button @click="itemToEdit = item.license; show = 'edit'; editItem(item)" class="edit-button">Edit</button>
        </td>
      </tr>
    </table>
    <p v-if="!data.length && !isLoading">No records found.</p>
    <p v-if="isLoading">Loading...</p>
    <ConfirmDialog v-if="show === 'confirm'" @confirm="removeItem(itemToRemove)" @cancel="show = 'default'"/>
  </div>
</template>

<script>
import axios from "axios";
import ConfirmDialog from "./ConfirmDialog.vue";
import ExportData from "./ExportData.vue";

export default {
  data() {
    return {
      data: [],
      isLoading: true,
      show: "default",
      itemToRemove: null,
      itemToEdit: null,
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
    ConfirmDialog,
  },
  beforeMount() {
    this.fetchData();
  },
  methods: {
    search() {
      this.data = this.data.filter(item => item.license.includes(this.searchTerm) || (''+ item.capacity).includes(this.searchTerm));
    },
    fetchData() {
      const url = "http://localhost:8080/vehicle";
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
    cancel() {
      document.getElementById("input_capacity").value = "";
      document.getElementById("input_route_id").value = "";
      this.show = "default";
    },
    editItem(item) {
      setTimeout(() => {document.getElementById("input_capacity").value = item.capacity}, 50);
      setTimeout(() => {document.getElementById("input_route_id").value = item.route_id.Valid ? item.route_id.Int64 : ''}, 50);
    },
    confirmEditItem() {
      const license = this.itemToEdit;
      const capacity = document.getElementById("input_capacity").value;
      const route_id = document.getElementById("input_route_id").value;
      document.getElementById("input_capacity").value = "";
      document.getElementById("input_route_id").value = "";
      this.show = "default";
      const url = "http://localhost:8080/vehicle/edit?license=" + license + "&capacity=" + capacity + "&route_id=" + route_id;
      console.log(url);
      axios.post(url)
        .then(response => {
          console.log(response);
        })
        .catch(error => {
          console.error("Error fetching data:", error);
        });
      this.fetchData();
    },
    addItem() {
      const license = document.getElementById("input_license").value;
      const capacity = document.getElementById("input_capacity").value;
      const route_id = document.getElementById("input_route_id").value;
      document.getElementById("input_capacity").value = "";
      document.getElementById("input_route_id").value = "";
      this.show = "default";
      const url = "http://localhost:8080/vehicle/add?license=" + license + "&capacity=" + capacity + "&route_id=" + route_id;
      axios.post(url)
        .then(response => {
          console.log(response);
        })
        .catch(error => {
          console.error("Error fetching data:", error);
        });
      this.fetchData();
    },
    sortByLicense() {
      this.data = this.data.sort((a, b) => {
        if (a.license < b.license) return -1;
        if (a.license > b.license) return 1;
        return 0;
      });
    },
    sortByCapacity() {
      this.data = this.data.sort((a, b) => {
        return a.capacity - b.capacity;
      });
    },
    sortByRouteId() {
      this.data = this.data.sort((a, b) => {
        return a.route_id.Int64 - b.route_id.Int64;
      });
    }
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

