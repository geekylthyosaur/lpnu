<template>
  <div>
    <input type="text" v-model="searchTerm" id="input_search" @input="search" placeholder="Search" class="input-field">
    <ExportData :table="'driver'"/>
    <button @click="show = 'add'" class="add-button">Add</button>
    <div v-if="show === 'add' || show === 'edit'">
      <input type="text" id="input_name" placeholder="Name" class="input-field">
      <input type="text" id="input_vehicle_id" placeholder="Vehicle Id" class="input-field">
      <br>
      <button v-if="show === 'add'" @click="addItem" class="add-button">Add</button>
      <button v-if="show === 'edit'" @click="confirmEditItem" class="add-button">Edit</button>
      <button @click="cancel" class="add-button">Cancel</button>
    </div>
    <table v-if="data.length" class="data">
      <tr>
        <td @click="sortById">Id</td>
        <td @click="sortByName">Name</td>
        <td @click="sortByVehicleId">Vehicle Id</td>
        <td></td>
      </tr>
      <tr v-for="item in data" :key="item.id">
        <td>{{ item.id }}</td>
        <td>{{ item.name }}</td>
        <td>{{ item.vehicle_id.String }}</td>
        <td style="text-align: center; width: 200px">
          <button @click="itemToEdit = item.id; show = 'edit'; editItem(item)" class="edit-button">Edit</button>
          <button @click="itemToRemove = item.id; show = 'confirm'" class="remove-button">Remove</button>
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
      this.data = this.data.filter(item => item.name.includes(this.searchTerm) || item.vehicle_id.String.includes(this.searchTerm) || (''+ item.id).includes(this.searchTerm));
    },
    sortById() {
    this.data.sort((a, b) => {
      return a.id - b.id;
    });
  },
      sortByVehicleId() {
    this.data = this.data.sort((a, b) => {
      if (a.vehicle_id.String < b.vehicle_id.String) return -1;
      if (a.vehicle_id.String > b.vehicle_id.String) return 1;
      return 0;
    });
  },

  sortByName() {
    this.data.sort((a, b) => {
      if (a.name < b.name) return -1;
      if (a.name > b.name) return 1;
      return 0;
    });
  },
    fetchData() {
      const url = "http://localhost:8080/driver";
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
      document.getElementById("input_name").value = "";
      document.getElementById("input_vehicle_id").value = "";
      this.show = "default";
    },
    removeItem(id) {
      this.show = "default";
      const url = "http://localhost:8080/driver/delete?id=" + id;
      axios.delete(url)
        .then(response => {
          console.log(response);
        })
        .catch(error => {
          console.error("Error fetching data:", error);
        });
      this.data = this.data.filter(item => item.id !== id);
      this.itemToRemove = null;
    },
    editItem(item) {
      setTimeout(() => {document.getElementById("input_name").value = item.name}, 50);
      setTimeout(() => {document.getElementById("input_vehicle_id").value = item.vehicle_id.String}, 50);
    },
    confirmEditItem() {
      const id = this.itemToEdit;
      const name = document.getElementById("input_name").value;
      const vehicle_id = document.getElementById("input_vehicle_id").value;
      document.getElementById("input_name").value = "";
      document.getElementById("input_vehicle_id").value = "";
      this.show = "default";
      const url = "http://localhost:8080/driver/edit?name=" + name + "&vehicle_id=" + vehicle_id + "&id=" + id;
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
      const name = document.getElementById("input_name").value;
      const vehicle_id = document.getElementById("input_vehicle_id").value;
      document.getElementById("input_name").value = "";
      document.getElementById("input_vehicle_id").value = "";
      this.show = "default";
      const url = "http://localhost:8080/driver/add?name=" + name + "&vehicle_id=" + vehicle_id;
      axios.post(url)
        .then(response => {
          console.log(response);
        })
        .catch(error => {
          console.error("Error fetching data:", error);
        });
      this.fetchData();
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
