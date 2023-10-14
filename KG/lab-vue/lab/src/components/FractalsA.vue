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
        <canvas id="viewport" width="400" height="400" style="width: 400px; height: 400px;" @wheel="onWheel" @mousedown="onMouseDown"></canvas>
      </div>
    </div>
  </div>
</template>

<script>
  export default {
    name: 'FractalsA',
    data() {
      return {
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
      onWheel(event) {
        var pos = this.getMousePos(event);
        this.zoomFractal(pos.x, pos.y, 2, event.deltaY < 0);
        this.generateImage();
      },
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
        for (var y = 0; y < this.canvas.height; y++) {
          for (var x = 0; x < this.canvas.width; x++) {
            this.iterate(x, y);
          }
        }
      },
      iterate(x, y) {
        var maxIter = 20;
        var x0 = (x + this.offsetx + this.panx) / this.zoom;
        var y0 = (y + this.offsety + this.pany) / this.zoom;
        
        var a = 0;
        var b = 0;
        var rx = 0;
        var ry = 0;
        
        var iterations = 0;
        while (iterations < maxIter && (rx * rx + ry * ry <= 4)) {
          rx = a * a - b * b + x0;
          ry = 2 * a * b + y0;
          
          a = rx;
          b = ry;
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
</style>
  