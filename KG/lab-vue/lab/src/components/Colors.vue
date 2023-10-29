<template>
  <div v-if="isLoaded" class="d-flex justify-content-center align-items-center" style="height: 540px; width: 800px;">
    <div class="text-center" v-if="!isLoaded">
      <input type="file" @change="openImage" style="display: none" ref="fileInput" accept="image/*">
      <button class="btn btn-custom" @click="selectFile">
        Завантажити файл
      </button>
      <p style="color: #bebebe; margin-top: -13px; font-size: small;">Оберіть файл щоб розпочати</p>
    </div>
  </div>
  <div v-if="!isLoaded" class="d-flex justify-content-center align-items-center" style="height: 540px; width: 800px;">
    <div class="col" style="max-width: 343px;">
  <div class="row d-flex justify-content-center">
    <div class="btn btn-custom d-flex justify-content-center" style="margin-top: 13px;">
      Вибрати колір
      <input style="margin-left: 30px; margin-top: 3px;" type="color" value="#400000" name="" id="color" @change="generatePalette(); generateImage()">
    </div>
  </div>
  <div class="row d-flex justify-content-center" style="margin-top: 367px;">
    <div class="btn btn-custom" @click="saveImage">Зберегти зображення</div>
  </div>
</div>
<div class="vr align-self-center" style="height: 100%; width: 3px; border: none; background-color: #bebebe;"></div>
<div class="col align-self-center">
  <div class="row d-flex justify-content-center">
    <div class="d-flex justify-content-center align-items-center" style="width: 400px; height: 400px; position: relative;">
      <canvas id="leftCanvas" @mousedown="startResize" width="400" height="400" style="width: 50%; height: 100%; background-color: blue;"></canvas>
      <canvas id="rightCanvas" @mousedown="startResize" width="400" height="400" style="width: 50%; height: 100%; background-color: red;"></canvas>
    </div>
    <div class="d-flex justify-content-center">
      <div class="align-items-left" style="margin-right: 300px; color: #bebebe; font-size: small;">До</div>
      <div class="align-items-right" style="color: #bebebe; font-size: small;">Після</div>
    </div>
  </div>
</div>

  </div>
</template>

<script>
export default {
  name: 'ColorS',
  data() {
    return {
      isLoaded: false,
      resizing: false,
      initialX: 0,
      leftCanvasWidth: 50,
    }
  },
  methods: {
    selectFile() {
      this.$refs.fileInput.click();
    },
    openImage(event) {
      const selectedFile = event.target.files[0];

      if (selectedFile) {
        this.isLoaded = true;
        console.log("Selected image:", selectedFile);
      }
    },
    startResize(e) {
      this.resizing = true;
      this.initialX = e.clientX;
      document.addEventListener('mouseup', this.stopResize);
      document.addEventListener('mousemove', this.resize);
    },
    resize(e) {
      if (this.resizing) {
        const diffX = e.clientX - this.initialX;
        let leftCanvas = document.getElementById("leftCanvas");
        let rightCanvas = document.getElementById("rightCanvas");
        let newLeftWidth = this.leftCanvasWidth + (diffX / 400) * 100;
        let newRightWidth = 100 - newLeftWidth;
        if (newLeftWidth > 90) newLeftWidth = 90;
        if (newRightWidth > 90) newRightWidth = 90;
        if (newLeftWidth < 10) newLeftWidth = 10;
        if (newRightWidth < 10) newRightWidth = 10;
        leftCanvas.style.width = `${newLeftWidth}%`;
        rightCanvas.style.width = `${newRightWidth}%`;
      }
    },
    stopResize() {
      this.resizing = false;
      this.leftCanvasWidth = parseFloat(document.getElementById("leftCanvas").style.width);
    },
  }
}
</script>

<style scoped>
.btn-custom {
  font-size: 22px;
  margin-bottom: 13px;
  border-radius: 24px;
  height: 56px;
  width: 306px;
  background-color: #ebebeb;
  border: 3px solid #ebebeb;
}
.btn:active {
  border: 3px solid #bebebe;
  background-color: #ebebeb;
}
.active {
  border: 3px solid #bebebe;
  background-color: #ebebeb;
}
</style>
    