<template>
  <Main/>
</template>

<script>
import Main from './components/Main.vue'

export default {
  name: 'App',
  components: {
    Main
  }
}
</script>

<style>
html {
  width: 800px;
  height: 600px;
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  border: 2px solid #000;
}
</style>
