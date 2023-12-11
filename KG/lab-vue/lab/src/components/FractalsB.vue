<template>
  <div class="d-flex" style="height: 540px; width: 800px;">
    <div class="col" style="max-width: 343px;">
      <div class="row d-flex flex-column align-items-center">
        <div class="btn btn-custom d-flex justify-content-center" style="margin-top: 13px;">
          Вибрати колір
          <input style="margin-left: 30px; margin-top: 3px;" type="color" value="#400000" id="color" @change="update">
        </div>
      </div>
      <div class="row d-flex justify-content-center" style="margin-top: 13px;">
        <div class="btn-i btn-custom-i d-flex flex-column align-items-center" style="margin-top: 0px; position: relative;">
          <span style="margin-top: -3px; margin-left: -35px;">Густина</span>
          <input v-model="density" style="margin-top: -8px; margin-left: -35px; width: 200px;" type="range" id="density" min="0.01" max="1.0" step="0.01" value="0.2">
          <span style="font-size: 20px; position: absolute; top: 50%; transform: translateY(-50%); right: 10px;">{{ parseFloat(density).toFixed(1) }}</span>
        </div>
      </div>
      <div class="row d-flex justify-content-center">
        <div class="btn-i btn-custom-i d-flex flex-column align-items-center" style="margin-top: 0px; position: relative;">
          <span style="margin-top: -3px; margin-left: -35px;">Відношення маси</span>
          <input v-model="massRatio" style="margin-top: -8px; margin-left: -35px; width: 200px;" type="range" id="mass-ratio"  min="0.01" max="1.01" step="0.01" value="0.2">
          <span style="font-size: 20px; position: absolute; top: 50%; transform: translateY(-50%); right: 10px;">{{ parseFloat(massRatio).toFixed(1) }}</span>
        </div>
      </div>
      <div class="row d-flex justify-content-center">
        <div class="btn-i btn-custom-i d-flex flex-column align-items-center" style="margin-top: 0px; position: relative;">
          <span style="margin-top: -3px; margin-left: -35px;">Довжина сліду</span>
          <input v-model="traceLength" style="margin-top: -8px; margin-left: -35px; width: 200px;" id="traceLength" type="range" min="1" max="10001" step="10">
          <span style="font-size: 20px; position: absolute; top: 50%; transform: translateY(-50%); right: 10px;">{{ parseFloat(traceLength / 1000).toFixed(0) }}</span>
        </div>
      </div>
      <div class="row d-flex justify-content-center" style="margin-top: 154px;">
        <div class="btn btn-custom" @click="saveImage">Зберегти зображення</div>
      </div>
    </div>
    <div class="vr align-self-center" style="height: 100%; width: 3px; border: none; background-color: #bebebe;"></div>
    <div class="col align-self-center">
      <div class="row d-flex justify-content-center">
        <div class="d-flex justify-content-center align-items-center" style="min-width: 400px; min-height: 400px;">
          <canvas id="viewport" width="400" height="400" style="width: 400px; height: 400px; background-color: #ebebeb;" @mousedown="onMouseDown"></canvas>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  export default {
    name: 'FractalsB',
    data() {
      return {
        color: "#370F0F",
        density: 1.0,
        massRatio: 0.2,
        traceLength: 10000,
        particle: {
            x: 200,
            y: 200,
            velocity: { dx: 0, dy: 0 }
        },
        traces: [],
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
      update() {
        this.massRatio = document.getElementById('mass-ratio').value;
        this.density = document.getElementById('density').value;
        this.color = document.getElementById('color').value;
        this.traceLength = document.getElementById('traceLength').value;
        this.traces = this.traces.slice(0, this.traceLength);
      },
      updateParticle() {
        if (Math.random() > 1.0 - this.density) {
          this.particle.velocity.dx = ((Math.random() * 2 - 1) / 1) / this.massRatio;
          this.particle.velocity.dy = ((Math.random() * 2 - 1) / 1) / this.massRatio;
        }

        this.particle.x += this.particle.velocity.dx;
        this.particle.y += this.particle.velocity.dy;

        if (this.particle.x < 0 || this.particle.x > this.canvas.width) {
          this.particle.velocity.dx *= -1;
        }
        if (this.particle.x < 0) {
          this.particle.x = 0;
        }
        if (this.particle.x > this.canvas.width) {
          this.particle.x = this.canvas.width;
        }
        if (this.particle.y < 0 || this.particle.y > this.canvas.height) {
          this.particle.velocity.dy *= -1;
        }
        if (this.particle.y < 0) {
          this.particle.y = 0;
        }
        if (this.particle.y > this.canvas.height) {
          this.particle.y = this.canvas.height;
        }

        this.traces.push({ x: this.particle.x, y: this.particle.y });

        if (this.traces.length > this.traceLength) {
          this.traces.shift();
        }
      },
      drawParticle() {
        this.context.clearRect(0, 0, this.canvas.width, this.canvas.height);
        this.context.fillStyle = this.color;

        this.context.strokeStyle = this.color;
        this.context.beginPath();
        this.context.moveTo(this.traces[0].x, this.traces[0].y);
        for (var trace of this.traces) {
          this.context.lineTo(trace.x, trace.y);
        }
        this.context.stroke();

        this.context.fillStyle = this.color;
        this.context.fillRect(this.particle.x - 3, this.particle.y - 3, 6, 6);
      },
      render() {
        this.updateParticle();
        this.drawParticle();
        requestAnimationFrame(this.render);
      },
      saveImage() {
        var img = new Image();
        img.src = this.canvas.toDataURL('image/png');
        var downloadLink = document.createElement('a');
        downloadLink.href = img.src;
        downloadLink.download = 'brownian.png';
        downloadLink.click();
        downloadLink.remove();
      },
    },
    mounted() {
      this.$emit('help', 'fractalsB');
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
.btn-custom-i {
  font-size: 22px;
  margin-bottom: 13px;
  border-radius: 24px;
  height: 56px;
  width: 306px;
  background-color: #bebebe; 
  background-image: linear-gradient(to right, #ebebeb 85%, rgba(0,0,0,0) 20%); 
  border: 3px solid #ebebeb;
}
.btn-i:active {
  border: 3px solid #bebebe;
  background-color: #bebebe;
  background-image: linear-gradient(to right, #ebebeb 85%, rgba(0,0,0,0) 20%); 
}
</style>
  