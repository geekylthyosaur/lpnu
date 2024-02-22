<template>
  <header-bar v-if="currentWindow != 'Головна'" @switchTo="switchTo" :title="currentWindow" :help="help"/>
  <fractals-a v-if="currentWindow == 'Фрактал Мандельброта'" @help="setHelp"/>
  <fractals-b v-if="currentWindow == 'Броунівський рух'" @help="setHelp"/>
  <colors v-if="currentWindow == 'Колірні схеми'" @help="setHelp"/>
  <moving-images v-if="currentWindow == 'Рухомі зображення'" @help="setHelp"/>
  <materials v-if="currentWindow == 'Матеріали'" @help="setHelp"/>
  <tests v-if="currentWindow == 'Опитувальник'" @help="setHelp"/>

  <main-window v-if="currentWindow == 'Головна'" @switchTo="switchTo"/>
</template>

<script>
import MainWindow from './components/Main.vue'
import HeaderBar from './components/Header.vue'
import FractalsA from './components/FractalsA.vue'
import FractalsB from './components/FractalsB.vue'
import ColorS from './components/Colors.vue'
import MovingImages from './components/MovingImages.vue'
import Materials from './components/Materials.vue'
import Tests from './components/Tests.vue'

export default {
  name: 'App',
  components: {
    'main-window': MainWindow,
    'header-bar': HeaderBar,
    'fractals-a': FractalsA,
    'fractals-b': FractalsB,
    'colors': ColorS,
    'moving-images': MovingImages,
    'materials': Materials,
    'tests': Tests,
  },
  data() {
    return {
      currentWindow: 'Головна',
      help: '',
    }
  },
  methods: {
    switchTo(window) {
      this.currentWindow = window;
    },
    setHelp(help) {
      this.help = help;
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
