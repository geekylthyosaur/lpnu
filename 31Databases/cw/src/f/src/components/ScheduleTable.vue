<template>
  <div>
    <SearchRoute :label="'Select route:'" @route-selected="routeSelected" />
    <br>
    <SearchStop v-if="selectedRouteId" :label="'Select stop:'" @stop-selected="stopSelected"/>
    <br>
    <button v-if="!isLoading" @click="show = 'add'" class="add-button">Add</button>
    <div v-if="(show === 'add' || show === 'edit') && !isLoading">
      <VueDatePicker v-model="time" time-picker :range="{ partialRange: false }" enable-seconds style="width: 300px; margin-left: 550px;"/>
      <br>
      <button v-if="show === 'add'" @click="addItem" class="add-button">Add</button>
      <button v-if="show === 'edit'" @click="confirmEditItem" class="add-button">Edit</button>
      <button @click="cancel" class="add-button">Cancel</button>
    </div>
    <table v-if="data.length" class="data">
      <tr>
        <td>Arrival</td>
        <td>Departure</td>
        <td></td>
      </tr>
      <tr v-for="item in data" :key="item.id">
        <td>{{ formatTime(item.arr) }}</td>
        <td>{{ formatTime(item.dep) }}</td>
        <td style="text-align: center; width: 200px">
          <button @click="itemToRemove = item.id; show = 'confirm'" class="remove-button">Remove</button>
        </td>
      </tr>
    </table>
    <p v-if="!data.length && !isLoading">No records found.</p>
    <ConfirmDialog v-if="show === 'confirm'" @confirm="removeItem(itemToRemove)" @cancel="show = 'default'"/>
  </div>
</template>

<script>
import axios from "axios";
import ConfirmDialog from "./ConfirmDialog.vue";
import SearchStop from "./SearchStop.vue";
import SearchRoute from "./SearchRoute.vue";
import VueDatePicker from '@vuepic/vue-datepicker';
import '@vuepic/vue-datepicker/dist/main.css';

export default {
  data() {
    return {
      data: [],
      isLoading: true,
      show: "default",
      itemToRemove: null,
      itemToEdit: null,
      selectedRouteId: null,
      selectedStopId: null,
      time: [],
    };
  },
  watch: {
    selectedRouteId() {
      if (this.selectedRouteId && this.selectedStopId) {this.fetchData();}
    },
    selectedStopId() {
      if (this.selectedRouteId && this.selectedStopId) {this.fetchData();}
    },
    time(t) {
      console.log(t);
    },
  },
  components: {
    ConfirmDialog,
    SearchStop,
    SearchRoute,
    VueDatePicker,
  },
  methods: {
    fetchData() {
      const route_id = this.selectedRouteId;
      const stop_id = this.selectedStopId;
      const url = `http://localhost:8080/schedule?route_id=${route_id}&stop_id=${stop_id}`;
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
    routeSelected(route) {
      this.selectedRouteId = route.id;
    },
    stopSelected(stop) {
      this.selectedStopId =stop.id;
    },
    cancel() {
      this.show = "default";
    },
    removeItem(id) {
      this.show = "default";
      const url = "http://localhost:8080/schedule/delete?id=" + id;
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
    formatTime(timeString) {
      const date = new Date(timeString);
      const hours = date.getUTCHours().toString().padStart(2, '0');
      const minutes = date.getUTCMinutes().toString().padStart(2, '0');
      const seconds = date.getUTCSeconds().toString().padStart(2, '0');
      return `${hours}:${minutes}:${seconds}`;
    },
    addItem() {
      this.show = "default";
      const arr= `${this.time[0].hours.toString().padStart(2, '0')}:${this.time[0].minutes.toString().padStart(2, '0')}:${this.time[0].seconds.toString().padStart(2, '0')}`;
      const dep= `${this.time[1].hours.toString().padStart(2, '0')}:${this.time[1].minutes.toString().padStart(2, '0')}:${this.time[1].seconds.toString().padStart(2, '0')}`;
      const route_id = this.selectedRouteId;
      const stop_id = this.selectedStopId;
      const url = `http://localhost:8080/schedule/add?arr=${arr}&dep=${dep}&route_id=${route_id}&stop_id=${stop_id}`;
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
