<template>
  <RouteWithStops hidden/>
  <ArrivalIn/>
</template>

<script>
import RouteWithStops from './components/RouteWithStops.vue'
import ArrivalIn from './components/ArrivalIn.vue'

export default {
  name: 'App',
  components: {
    RouteWithStops,
    ArrivalIn,
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
