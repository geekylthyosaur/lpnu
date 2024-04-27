<template>
  <div>
    <table v-if="data.length" class="data">
      <tr>
        <td>Id</td>
        <td>Name</td>
        <td></td>
      </tr>
      <tr v-for="item in data" :key="item.id">
        <td>{{ item.id }}</td>
        <td>{{ item.name }}</td>
        <td style="text-align: center; width: 150px">
          <button @click="editItem(item.id)" class="edit-button">Edit</button>
          <button @click="itemToRemove = item.id; show = 'confirm'" class="remove-button">Remove</button>
          <ConfirmDialog v-if="show === 'confirm'" @confirm="removeItem(itemToRemove)" @cancel="show = 'default'"/>
        </td>
      </tr>
    </table>
    <p v-else>No records found.</p>
    <p v-if="isLoading">Loading...</p>
  </div>
</template>

<script>
import axios from "axios";
import ConfirmDialog from "./ConfirmDialog.vue";

export default {
  props: {
    table: {
      type: String,
      required: true,
    }
  },
  data() {
    return {
      data: [],
      isLoading: true,
      show: "default",
      itemToRemove: null,
    };
  },
  components: {
    ConfirmDialog,
  },
  beforeMount() {
    this.fetchData();
  },
  methods: {
    fetchData() {
      const url = "http://localhost:8080/" + this.table;
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
    removeItem(id) {
      this.show = "default";
      const url = "http://localhost:8080/" + this.table + "/delete?id=" + id;
      axios.post(url)
        .catch(error => {
          console.error("Error fetching data:", error);
          this.isLoading = false;
        });
      this.data = this.data.filter(item => item.id !== id);
      this.itemToRemove = null;
    },
    editItem() {
    },
  }
}
</script>

<style scoped>
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

.edit-button,
.remove-button {
  padding: 5px 10px;
  margin-right: 5px;
  border: none;
  border-radius: 5px;
  cursor: pointer;
  transition: background-color 0.3s ease, color 0.3s ease;
}

.edit-button {
  background-color: dodgerblue;
  color: white;
}

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
</style>
