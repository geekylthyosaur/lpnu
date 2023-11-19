<template>
  <canvas hidden ref="canvas"></canvas>
  <div v-if="!isLoaded" class="d-flex justify-content-center align-items-center" style="height: 540px; width: 800px;">
    <div class="text-center" v-if="!isLoaded">
      <input type="file" @change="openImage" style="display: none" ref="fileInput" accept="image/*">
      <button class="btn btn-custom" @click="selectFile">
        Завантажити файл
      </button>
      <p style="color: #bebebe; margin-top: -13px; font-size: small;">Оберіть файл щоб розпочати</p>
    </div>
  </div>
  <div v-if="isLoaded" class="d-flex justify-content-center align-items-center" style="height: 540px; width: 800px;">
    <div class="col" style="max-width: 343px;">
      <div class="row d-flex justify-content-center" style="margin-top: 13px;">
        <div class="btn btn-custom d-flex flex-column align-items-center">
          <span style="margin-top: -8px;">Насиченість зеленого</span>
          <input v-model="saturation" style="margin-top: -8px; width: 200px;" type="range" min="0.0" max="1.0" step="0.01">
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
          <canvas ref="leftCanvas" @mousemove="showPixelInfo" @mouseover="showPixelInfo" @mouseout="this.pixelInfo=null" @mousedown="startResize" width="400" height="400" style="width: 50%; height: 100%; background-color: blue; border-right: 3px solid #bebebe"></canvas>
          <canvas ref="rightCanvas" style="width: 50%; height: 100%; background-color: red;" @mousemove="showPixelInfo" @mouseover="showPixelInfo" @mouseout="this.pixelInfo=null" @mousedown="startResize" width="400" height="400"></canvas>
        </div>
        <div ref="pixelInfoPopup" v-if="this.pixelInfo" class="pixel-info-popup d-flex col">
          <div class=" d-flex row align-items-center justify-content-center align-items-center" style="margin-left: 0px;">
            <p style="">RGB: {{ pixelInfo.rgb }}</p>
            <p style="margin-top: -13px;">HSV: ({{ pixelInfo.hsv.h }}, {{ pixelInfo.hsv.s }}, {{ pixelInfo.hsv.v }})</p>
          </div>
          <canvas ref="colorPreview" class="color-preview" style="width: 25px; height: 25px; margin-right: 13px; margin-top: auto; margin-bottom: auto;" width="25" height="25"></canvas>
        </div>
        <div class="d-flex justify-content-center">
          <div class="align-items-left" style="margin-right: 300px; color: #aaaaaa; font-size: small;">До</div>
          <div class="align-items-right" style="color: #aaaaaa; font-size: small;">Після</div>
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
      currLeftCanvasWidth: 50,
      imgBefore: null,
      imgAfter: null,
      pixelInfo: null,
      saturation: 0.5,
    }
  },
  watch: {
    saturation: function () {
      this.drawImage();
    },
  },
  methods: {
    selectFile() {
      this.$refs.fileInput.click();
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
        let newLeftWidth = this.leftCanvasWidth + (diffX / 400) * 100;
        let newRightWidth = 100 - newLeftWidth;
        if (newLeftWidth > 90) newLeftWidth = 90;
        if (newRightWidth > 90) newRightWidth = 90;
        if (newLeftWidth < 10) newLeftWidth = 10;
        if (newRightWidth < 10) newRightWidth = 10;
        this.$refs.leftCanvas.style.width = `${newLeftWidth}%`;
        this.$refs.rightCanvas.style.width = `${newRightWidth}%`;
        this.currLeftCanvasWidth = parseFloat(this.$refs.leftCanvas.style.width);
        this.drawImage();
      }
    },
    stopResize() {
      this.resizing = false;
      this.leftCanvasWidth = parseFloat(this.$refs.leftCanvas.style.width);
      this.currLeftCanvasWidth = parseFloat(this.$refs.leftCanvas.style.width);
      document.removeEventListener('mouseup', this.stopResize);
      document.removeEventListener('mousemove', this.resize);

      this.drawImage();
    },
    openImage(event) {      
      const selectedFile = event.target.files[0];

      if (selectedFile) {
        this.isLoaded = true;

        const img = new Image();
        img.src = URL.createObjectURL(selectedFile);

        img.onload = () => {
          this.imgBefore = img;
          this.imgAfter = img;
          this.drawImage()
        };
      }
    },
    drawImage() {
      const leftCanvas = this.$refs.leftCanvas;
      const rightCanvas = this.$refs.rightCanvas;
      const canvas = this.$refs.canvas;

      const leftContext = leftCanvas.getContext('2d');
      const rightContext = rightCanvas.getContext('2d');
      const context = canvas.getContext('2d');

      leftContext.clearRect(0, 0, leftCanvas.width, leftCanvas.height);
      rightContext.clearRect(0, 0, rightCanvas.width, rightCanvas.height);
      context.clearRect(0, 0, canvas.width, canvas.height);

      const originalWidth = this.imgBefore.width;
      const originalHeight = this.imgBefore.height;
      const leftCanvasWidth = (this.currLeftCanvasWidth / 100) * originalWidth;
      const rightCanvasWidth = originalWidth - leftCanvasWidth;

      leftContext.drawImage(this.imgBefore, 0, 0, leftCanvasWidth, originalHeight, 0, 0, leftCanvas.width, leftCanvas.height);
      rightContext.drawImage(this.imgAfter, leftCanvasWidth, 0, rightCanvasWidth, originalHeight, 0, 0, rightCanvas.width, rightCanvas.height);
      context.drawImage(this.imgAfter, 0, 0);

      const imageData = rightContext.getImageData(0, 0, rightCanvas.width, rightCanvas.height);
      const data = imageData.data;
      this.modifyImage(data);
      rightContext.putImageData(imageData, 0, 0);
    },
    modifyImage(data) {
      for (let i = 0; i < data.length; i += 4) {
        var hsv = this.rgbToHsv(data[i], data[i + 1], data[i + 2]);
        if (Math.abs(hsv.h - 120) < 40) {
          hsv.s = this.saturation * 100;

          var rgb = this.hsvToRgb(hsv.h, hsv.s, hsv.v);
          data[i] = rgb.r;
          data[i + 1] = rgb.g;
          data[i + 2] = rgb.b;
        }
      }
    },
    saveImage() {
      const canvas = document.createElement('canvas');
      const context = canvas.getContext('2d');

      const canvasWidth = this.imgBefore.width;
      const canvasHeight = this.imgBefore.height;

      canvas.width = canvasWidth;
      canvas.height = canvasHeight;

      context.clearRect(0, 0, canvasWidth, canvasHeight);

      context.drawImage(this.imgAfter, 0, 0, canvasWidth, canvasHeight);

      const imageData = context.getImageData(0, 0, canvas.width, canvas.height);
      const data = imageData.data;
      this.modifyImage(data);
      context.putImageData(imageData, 0, 0);

      const dataURL = canvas.toDataURL('image/png');

      const link = document.createElement('a');
      link.href = dataURL;
      link.download = 'modified_image.png';
      link.click();
    },
    showPixelInfo(event) {
      const leftCanvas = this.$refs.leftCanvas;
      const rightCanvas = this.$refs.rightCanvas;
      const leftContext = leftCanvas.getContext('2d');
      const rightContext = rightCanvas.getContext('2d');

      const leftRect = leftCanvas.getBoundingClientRect();

      const x = event.clientX;
      const y = event.clientY;

      const isLeftCanvas = x >= leftRect.left && x <= leftRect.right && y >= leftRect.top && y <= leftRect.bottom;

      const canvas = isLeftCanvas ? leftCanvas : rightCanvas;
      const context = isLeftCanvas ? leftContext : rightContext;

      const canvasRect = canvas.getBoundingClientRect();
      const scaleX = canvas.width / canvasRect.width;
      const scaleY = canvas.height / canvasRect.height;

      const offsetX = (x - canvasRect.left) * scaleX;
      const offsetY = (y - canvasRect.top) * scaleY;

      const pixel = context.getImageData(offsetX, offsetY, 1, 1).data;

      const rgb = `(${pixel[0]}, ${pixel[1]}, ${pixel[2]})`;
      const hsv = this.rgbToHsv(pixel[0], pixel[1], pixel[2]);

      this.pixelInfo = { rgb, hsv };

      if (this.$refs.pixelInfoPopup && this.$refs.colorPreview) {
        var htmlElement = document.documentElement;

        var styles = window.getComputedStyle(htmlElement);

        var topValue = parseFloat(styles.getPropertyValue('top'));
        var leftValue = parseFloat(styles.getPropertyValue('left'));

        this.$refs.pixelInfoPopup.style.left = `${event.clientX - leftValue + 400}px`;
        this.$refs.pixelInfoPopup.style.top = `${event.clientY - topValue + 350}px`;

        const colorPreviewCanvas = this.$refs.colorPreview;
        const colorPreviewContext = colorPreviewCanvas.getContext('2d');
        colorPreviewContext.clearRect(0, 0, colorPreviewCanvas.width, colorPreviewCanvas.height);
        colorPreviewContext.fillStyle = `rgb(${pixel[0]}, ${pixel[1]}, ${pixel[2]})`;
        colorPreviewContext.fillRect(0, 0, colorPreviewCanvas.width, colorPreviewCanvas.height);
      }
    },
    rgbToHsv(r, g, b) {
      r /= 255, g /= 255, b /= 255;

      var max = Math.max(r, g, b), min = Math.min(r, g, b);
      var h, s, v = max;

      var d = max - min;
      s = max == 0 ? 0 : d / max;

      if (max == min) {
        h = 0;
      } else {
        switch (max) {
          case r: h = (g - b) / d + (g < b ? 6 : 0); break;
          case g: h = (b - r) / d + 2; break;
          case b: h = (r - g) / d + 4; break;
        }

        h /= 6;
      }

      return { h: Math.floor(h*360), s: Math.floor(s * 100), v: Math.floor(v * 100) };
    },
    hsvToRgb(h, s, v) {
      h /= 360, s /= 100, v /= 100;
      var r, g, b;

      var i = Math.floor(h * 6);
      var f = h * 6 - i;
      var p = v * (1 - s);
      var q = v * (1 - f * s);
      var t = v * (1 - (1 - f) * s);

      switch (i % 6) {
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
      }

      return { r: Math.floor(r * 255), g: Math.floor(g * 255), b: Math.floor(b * 255) };
    }
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
.pixel-info-popup {
  position: absolute;
  background-color: #fff;
  padding: 3px;
  border: 1px solid #ccc;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  max-width: 200px;
  max-height: 50px;
  font-size: small;
  border-radius: 13px;
}
</style>
    