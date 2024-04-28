<template>
  <div>
    <div style="display: flex; justify-content: center; align-items: center;">
    <VueDatePicker v-model="date" range style="width: 500px"/>
    <SearchRoute @route-selected="routeSelected" :label="'Select route:'" style="width: 700px"/>
</div>

    <Line
      :data="this.data"
      :options="this.options"
    />
  </div>
</template>

<script>
import axios from "axios";
import { Line } from 'vue-chartjs'
import { Chart as ChartJS, CategoryScale, LinearScale, PointElement, LineElement, Title, Tooltip, Legend } from 'chart.js'
import SearchRoute from "./SearchRoute.vue";
import VueDatePicker from '@vuepic/vue-datepicker';
import '@vuepic/vue-datepicker/dist/main.css';

ChartJS.register( CategoryScale, LinearScale, PointElement, LineElement, Title, Tooltip, Legend)


export default {
  components: {
    Line,
    SearchRoute,
    VueDatePicker,
  },
  data() {
    return {
      data: {labels: [], datasets: []},
      options: {
        responsive: true,
      },
      routeId: '',
      date: [],
    };
  },
  watch: {
    routeId() {
      this.fetchData();
    },
    date() {
      this.fetchData();
    }
  },
  beforeMount() {
    this.fetchData();
  },
  methods: {
    fetchData() {
      const params = {
        route_id: this.routeId,
        start_date: this.formatDate((this.date || [])[0]) || '',
        end_date: this.formatDate((this.date || [])[1]) || '',
      };

      const queryString = Object.keys(params)
        .map(key => encodeURIComponent(key) + '=' + encodeURIComponent(params[key]))
        .join('&');

      axios.get('http://localhost:8080/stats?' + queryString)
        .then(response => {
          let data = response.data;
          data = data.sort((a, b) => new Date(a.transaction_date) - new Date(b.transaction_date));
          const dates = data.map(item => this.formatDate(new Date(item.transaction_date)));
          const dailyTotals = data.map(item => item.daily_total);
          this.data = {
            labels: dates,
            datasets: [{
              label: "Income",
              data: dailyTotals,
            }],
          };
        })
        .catch(error => {
          console.error('Error:', error);
        });
    },
    formatDate(date) {
      if (!date) return;
      var day = date.getDate().toString().padStart(2, '0');
      var month = (date.getMonth() + 1).toString().padStart(2, '0'); // Month starts from 0
      var year = date.getFullYear();

      return day + '-' + month + '-' + year;
    },
    routeSelected(route) {
      this.routeId = route.id;
    },
  },
}
</script>

<style>
</style>
