<template>
  <div class="d-flex" style="height: 540px; width: 800px;">
    <div class="col d-flex justify-content-center" style="max-width: 343px;">
      <div class="row align-items-top">
        <div class="btn">abc</div>
      </div>
      <div class="row align-items-end">
        <div class="btn">abc</div>
      </div>
    </div>
    <div class="vr align-self-center" style="height: 100%; width: 3px; border: none; background-color: #bebebe;"></div>
    <div class="col align-self-center">
      <div class="row d-flex justify-content-center">
        <div class="d-flex justify-content-center align-items-center" style="position: relative; width: 400px; height: 400px;">
          <canvas id="viewport" width="400" height="400" style="width: 400px; height: 400px; background-color: black;" @mousedown="onMouseDown"></canvas>
          <i v-if="rendering" class="fa fa-spinner icon-loading" style="position: absolute; top: 42%; left: 46%;"></i>
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
        rendering: false,
        offsetx: -200,
        offsety: -200,
        panx: -100,
        pany: 0,
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
        console.log(pos);
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
          this.panx = factor * (x + this.offsetx + this.panx);
          this.pany = factor * (y + this.offsety + this.pany);
        } else {
          this.zoom /= factor;
          this.panx = (x + this.offsetx + this.panx) / factor;
          this.pany = (y + this.offsety + this.pany) / factor;
        }
      },
      generateImage() {
        this.rendering = true;
        for (var y = 0; y < this.canvas.height; y++) {
          for (var x = 0; x < this.canvas.width; x++) {
            setTimeout(this.iter, 1, x, y);
          }
        }
        this.rendering = false;
      },
      iter(x, y) {
        var maxIter = 250;
        
        var zx = 0;
        var zy = 0;
        var cx = (x + this.offsetx + this.panx) / this.zoom;
        var cy = (y + this.offsety + this.pany) / this.zoom;
        
        var iterations = 0;
        while (iterations < maxIter) {
          const newZx = zx * zx - zy * zy + cx;
          const newZy = 2 * zx * zy + cy;
          
          zx = newZx;
          zy = newZy;
    
          if (zx * zx + zy * zy > 4) {
            break;
          }
          
          iterations++;
        }
        
        var color;
        if (iterations == maxIter) {
            color = { r:0, g:0, b:0};
        } else {
            var index = Math.floor((iterations / (maxIter-1)) * 255);
            color = this.palette[index];
        }
        
        var pixelindex = (y * this.canvas.width + x) * 4;
        this.image.data[pixelindex] = color.r;
        this.image.data[pixelindex+1] = color.g;
        this.image.data[pixelindex+2] = color.b;
        this.image.data[pixelindex+3] = 255;
      },
      generatePalette() {
        var roffset = 24;
        var goffset = 16;
        var boffset = 0;
        for (var i = 0; i < 256; i++) {
          this.palette[i] = { r:roffset, g:goffset, b:boffset};
          
          if (i < 64) {
            roffset += 3;
          } else if (i<128) {
            goffset += 3;
          } else if (i<192) {
            boffset += 3;
          }
        }
      },
      render() {
        window.requestAnimationFrame(this.render);
        this.context.putImageData(this.image, 0, 0);
      },
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
.icon-loading {
  font-size: 48px;
  width: 48px;
  height: 48px;
  color: gray;
  position: fixed;
  transform: translateY(-200px);
  animation: spin 1s linear infinite;
}
@keyframes spin {
  0% { transform: rotate(0deg); }
  100% { transform: rotate(360deg); }
}
</style>
  