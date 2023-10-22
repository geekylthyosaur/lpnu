<template>
  <div class="d-flex" style="height: 540px; width: 800px;">
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
        <div class="d-flex justify-content-center align-items-center" style="width: 400px; height: 400px;">
          <canvas id="viewport" width="400" height="400" style="width: 400px; height: 400px; background-color: black;" @mousedown="onMouseDown"></canvas>
        </div>
      </div>
      <div class="row d-flex justify-content-center">
        <div class="btn btn-zoom btn-zoomout" @click="zoomOut">
          <i class="fa fa-search-minus icon-zoomout"></i>
        </div>
        <div class="btn btn-zoom btn-zoomin" @click="zoomIn">
          <i class="fa fa-search-plus icon-zoomin"></i>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  export default {
    name: 'FractalsA',
    data() {
      return {
        canvasOffsetX: -200,
        canvasOffsetY: -200,
        shiftX: -100,
        shiftY: 0,
        zoom: 150,
        palette: [],
      };
    },
    computed: {
      canvas() {
        return document.getElementById('viewport');
      },
      context() {
        return this.canvas.getContext("2d");
      },
      image() {
        return this.context.createImageData(this.canvas.width, this.canvas.height);
      },
    },
    methods: {
      onMouseDown(event) {
        var pos = this.getMousePos(event);
        this.zoomFractal(pos.x, pos.y, 1, false);
        this.generateImage();
      },
      getMousePos(event) {
        var rect = this.canvas.getBoundingClientRect();
        return {
          x: Math.round((event.clientX - rect.left)/(rect.right - rect.left)*this.canvas.width),
          y: Math.round((event.clientY - rect.top)/(rect.bottom - rect.top)*this.canvas.height)
        };
      },
      zoomIn() {
        this.zoomFractal(200, 200, 2, true);
        this.generateImage();
      },
      zoomOut() {
        this.zoomFractal(200, 200, 2, false);
        this.generateImage();
      },
      zoomFractal(x, y, factor, zoomin) {
        if (zoomin) {
          this.zoom *= factor;
          this.shiftX = factor * (x + this.canvasOffsetX + this.shiftX);
          this.shiftY = factor * (y + this.canvasOffsetY + this.shiftY);
        } else {
          this.zoom /= factor;
          this.shiftX = (x + this.canvasOffsetX + this.shiftX) / factor;
          this.shiftY = (y + this.canvasOffsetY + this.shiftY) / factor;
        }
      },
      generateImage() {
        for (var y = 0; y < this.canvas.height; y++) {
          setTimeout(this.generateRow, 10, y);
        }
      },
      generateRow(y) {
        for (var x = 0; x < this.canvas.width; x++) {
          this.iter(x, y);
        }
      },
      iter(x, y) {
        var maxIter = 250;
        
        // to make julia swap z and c and make cx -0.4 and cy 0.6
        // can it be ifs fractal? why not?
        // ifs cannot be used with non-linear fns
        // geometrycal fractals can be drawn with ifs (linear)
        // mandelbrot is похідний julia

        var zx = 0;
        var zy = 0;
        var cx = (x + this.canvasOffsetX + this.shiftX) / this.zoom;
        var cy = (y + this.canvasOffsetY + this.shiftY) / this.zoom;

        var i = 0;
        for (;zx * zx + zy * zy < 4 && i < maxIter; ++i) {
          const newZx = zx * zx - zy * zy + cx;
          const newZy = 2 * zx * zy + cy;

          zx = newZx;
          zy = newZy;
        }

        var index = Math.floor((i / (maxIter-1)) * 255);
        var color = this.palette[index] || { r:0, g:0, b:0};
        
        var pixelindex = (y * this.canvas.width + x) * 4;
        this.image.data[pixelindex] = color.r;
        this.image.data[pixelindex+1] = color.g;
        this.image.data[pixelindex+2] = color.b;
        this.image.data[pixelindex+3] = 255;
      },
      generatePalette() {
        var colorPicker = document.getElementById("color");
        var color = this.hexToRgb(colorPicker.value);
        var roffset = color.r;
        var goffset = color.g;
        var boffset = color.b;
        for (var i = 0; i < 256; i++) {
          this.palette[i] = { r:roffset, g:goffset, b:boffset};

          if (i < 85) {
            roffset += 2;
          } else if (i<170) {
            goffset += 2;
          } else if (i<255) {
            boffset += 2;
          }
        }
      },
      render() {
        window.requestAnimationFrame(this.render);
        this.context.putImageData(this.image, 0, 0);
      },
      saveImage() {
        var img = new Image();
        img.src = this.canvas.toDataURL('image/png');
        var downloadLink = document.createElement('a');
        downloadLink.href = img.src;
        downloadLink.download = 'mandelbrot.png';
        downloadLink.click();
        downloadLink.remove();
      },
      hexToRgb(hex) {
        hex = hex.replace(/^#/, '');

        var r = parseInt(hex.slice(0, 2), 16);
        var g = parseInt(hex.slice(2, 4), 16);
        var b = parseInt(hex.slice(4, 6), 16);

        return { r, g, b };
      }
    },
    mounted() {
      this.generatePalette();
      this.generateImage();
      this.render();
    },
  };
</script>

<style scoped>
.btn-zoom {
  width: 60px;
  height: 45px;
  background-color: #ebebeb;
  border: 3px solid #ebebeb;
  border-radius: 0;
  margin-top: 13px;
}
.btn-zoomin {
  margin-right: auto;
  border-top-right-radius: 12px;
  border-bottom-right-radius: 12px;
}
.btn-zoomout {
  margin-left: auto;
  border-top-left-radius: 12px;
  border-bottom-left-radius: 12px;
}
.btn-zoom:active {
  background-color: #ebebeb;
  border: 3px solid #bebebe;
}
.icon-zoomin, .icon-zoomout {
  font-size: 28px;
}
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
</style>
  