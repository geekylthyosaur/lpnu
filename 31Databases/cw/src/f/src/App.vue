<template>
  <AppHeader :authenticated="authenticated" @login="authenticated = true" @logout="authenticated = false"/>

  <SideBar v-if="role === 'passenger'" :buttons="['Search for routes', 'Time to arrival']" @click0="show = 'default'" @click1="show = 'arrivalIn'"/>
  <SideBar v-if="role === 'driver'" :buttons="['Fill maintenance']"/>
  <SideBar v-if="role === 'manager'" :buttons="['Drivers', 'Vehicles', 'Maintenance', 'Statistics']" @click0="show = 'default'" @click1="show = 'vehicles'" @click2="show = 'maintenance'" @click3="show = 'statistics'"/>

  <div class="content">
    <div v-if="!authenticated && role === 'passenger'">
      <RouteWithStops v-if="show === 'default'"/>
      <ArrivalIn v-if="show === 'arrivalIn'"/>
    </div>
    <div v-if="authenticated && role === 'driver'">
      <div v-if="show === 'default'">
        <InsertMaintenance/>
      </div>
    </div>
    <div v-if="authenticated && role === 'manager'">
      <DriverTable v-if="show === 'default'"/>
      <VehicleTable v-if="show === 'vehicles'"/>
      <MaintenanceTable v-if="show === 'maintenance'"/>
      <StatisticS v-if="show === 'statistics'"/>
    </div>
  </div>
</template>

<script>
import axios from 'axios';
import AppHeader from './components/AppHeader.vue'
import SideBar from './components/SideBar.vue'
import RouteWithStops from './components/RouteWithStops.vue'
import ArrivalIn from './components/ArrivalIn.vue'
import InsertMaintenance from './components/InsertMaintenance.vue'
import DriverTable from './components/DriverTable.vue'
import VehicleTable from './components/VehicleTable.vue'
import MaintenanceTable from './components/MaintenanceTable.vue'
import StatisticS from './components/StatisticS.vue'

export default {
  name: 'App',
  components: {
    AppHeader,
    SideBar,
    RouteWithStops,
    ArrivalIn,
    InsertMaintenance,
    DriverTable,
    VehicleTable,
    MaintenanceTable,
    StatisticS,
  },
  data() {
    return {
      role: localStorage.getItem('username') || 'passenger',
      authenticated: localStorage.getItem('username') !== null,
      show: 'default',
    };
  },
  watch: {
    authenticated() {
      this.role = localStorage.getItem('username') || 'passenger';
      this.setAuthHeader();
      this.show = 'default';
    },
  },
  beforeMount() {
    this.setAuthHeader();
  },
  methods: {
    setAuthHeader() {
      axios.defaults.headers.common['Authorization'] = this.role;
    },
  }
}
</script>

<style>
body,
html {
  margin: 0;
  padding: 0;
  font-family: Arial, sans-serif;
}

#app {
  text-align: center;
}

.content {
  margin-left: 20%;
  margin-top: 60px;
  padding: 3%;
}
</style>
