<template>
  <header-bar v-if="currentWindow != 'Головна'" @switchTo="switchTo" :title="currentWindow"/>
  <fractals-a v-if="currentWindow == 'Фрактал Мандельброта'"/>
  <fractals-b v-if="currentWindow == 'Броунівський рух'"/>

  <main-window v-if="currentWindow == 'Головна'" @switchTo="switchTo"/>
</template>

<script>
import MainWindow from './components/Main.vue'
import HeaderBar from './components/Header.vue'
import FractalsA from './components/FractalsA.vue'
import FractalsB from './components/FractalsB.vue'

export default {
  name: 'App',
  components: {
    'main-window': MainWindow,
    'header-bar': HeaderBar,
    'fractals-a': FractalsA,
    'fractals-b': FractalsB,
  },
  data() {
    return {
      currentWindow: 'Головна',
    }
  },
  methods: {
    switchTo(window) {
      this.currentWindow = window;
    }
  },
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
  background-color: black;
}
</style>
