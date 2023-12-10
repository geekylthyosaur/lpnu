<template>
  <div v-if="start" class="d-flex justify-content-center align-items-center" style="height: 540px; width: 800px;">
    <div style="text-align: center;">
      <span style="font-size: 15px; margin-bottom: 10px; display: block; color: #aaaaaa;">Щоб побудувати паралелограм,<br>виберіть три точки на площині</span>
      <div class="d-flex justify-content-center align-items-center" style="width: 400px; height: 400px;">
        <Line ref="chart" :data="chartData" :options="chartOptions" style="width: 400px; height: 400px;"></Line>
      </div>
    </div>
  </div>
  <div v-if="!start" class="d-flex" style="height: 540px; width: 800px;">
    <div class="col" style="max-width: 343px;">
      <div class="row d-flex justify-content-center">
        <div class="btn-i btn-custom-i d-flex flex-column align-items-center" style="margin-top: 13px; position: relative;">
          <span style="margin-top: -3px; margin-left: -35px;">Масштабування</span>
          <input v-model="scaleFactor" style="margin-top: -8px; margin-left: -35px; width: 200px;" type="range" min="0.9" max="1.1" step="0.05">
          <span style="font-size: 20px; position: absolute; top: 50%; transform: translateY(-50%); right: 10px;">{{ parseFloat(scaleFactor).toFixed(1) }}</span>
        </div>
        <div class="btn-i btn-custom-i d-flex flex-column align-items-center" style="margin-top: 13px; position: relative;">
          <span style="margin-top: -3px; margin-left: -35px;">Поворот</span>
          <input v-model="rotationFactor" style="margin-top: -8px; margin-left: -35px; width: 200px;" type="range" min="-4.0" max="4.0" step="0.1">
          <span style="font-size: 20px; position: absolute; top: 50%; transform: translateY(-50%); right: 10px;">{{ parseFloat(rotationFactor).toFixed(1) }}</span>
        </div>
      </div>
      <div class="row d-flex justify-content-center" style="margin-top: 298px;">
        <div class="btn btn-custom" @click="saveImage">Зберегти зображення</div>
      </div>
    </div>
    <div class="vr align-self-center" style="height: 100%; width: 3px; border: none; background-color: #bebebe;"></div>
    <div class="col align-self-center">
      <div class="row d-flex justify-content-center">
        <div class="d-flex justify-content-center align-items-center" style="width: 400px; height: 400px;">
          <Line ref="chart" :data="chartData" :options="chartOptions" style="width: 400px; height: 400px;"></Line>
        </div>
      </div>
      <div class="row d-flex justify-content-center">
        <div class="btn btn-playpause d-flex align-items-center justify-content-center" @click="play">
          <i v-if="!isPlaying" class="fa fa-play"></i>
          <i v-if="isPlaying" class="fa fa-pause"></i>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import { Line } from 'vue-chartjs'
import Chart from 'chart.js/auto';
import zoomPlugin from 'chartjs-plugin-zoom';
import { getRelativePosition } from 'chart.js/helpers';

export default {
  name: 'MovingImages',
  components: { Line },
  data() {
    return {
      start: true,
      isPlaying: false,
      animation: undefined,
      points: [],
      scaleFactor: 1.0,
      rotationFactor: 1.5,
      choosedPoint: 0,
    };
  },
  computed: {
    chartData() {
      return {
        datasets: [ { 
          data: [],
          pointBackgroundColor: (context) => (context.dataIndex === this.choosedPoint || context.dataIndex === 4 + this.choosedPoint) && !this.start ? '#aaaaaa' : '#ebebeb',
          pointBorderColor: '#aaaaaa',
          borderColor: '#bebebe',
          pointRadius: 8,
          pointHoverRadius: 13,
          pointHitRadius: 26,
        }],
      };
    },
    chartOptions() {
      const labels = ['A', 'B', 'C', 'D', 'A'];
      const title = (context) => {
        return labels[context[0].dataIndex];
      };
      const none = () => {
        return '';
      };
      return {
        responsive: false,
        scales: {
          x: {
            type: 'linear',
            position: 'center',
          },
          y: {
            type: 'linear',
            position: 'center',
          },
        },
        plugins: {
          tooltip: {
            callbacks: {
              title: title,
              label: none,
            }
          },
          legend: {
            display: false,
          },
          zoom: {
            pan: {
              enabled: true,
              mode: 'xy',
            },
            zoom: {
              wheel: {
                enabled: true,
              },
              mode: 'xy',
            },
            limits: {
              x: { min: -50, max: 50 },
              y: { min: -50, max: 50 },
            }
          },
        },
        onClick: (e) => {
          const chart = this.$refs.chart.chart;
          const canvasPosition = getRelativePosition(e, chart);
          const x = chart.scales.x.getValueForPixel(canvasPosition.x);
          const y = chart.scales.y.getValueForPixel(canvasPosition.y);
          if (this.start) {
            this.chartData.datasets[0].data.push([x, y]);
            this.points.push([x, y]);
            chart.update();
          } else {
            let closestDistance = Number.POSITIVE_INFINITY;
            let closestIndex = -1;

            for (let i = 0; i < this.chartData.datasets[0].data.length; i++) {
              const point = this.chartData.datasets[0].data[i];
              const distance = Math.sqrt((point[0] - x) ** 2 + (point[1] - y) ** 2);

              if (distance < closestDistance) {
                closestDistance = distance;
                closestIndex = i;
              }
            }

            this.choosedPoint = closestIndex;
            chart.update();
          }
        },
      }
    }
  },
  beforeMount() {
    Chart.register(zoomPlugin);
  },
  mounted() {
    this.$nextTick(() => {
      const chart = this.$refs.chart.chart;
      chart.zoom(-1000);
      chart.update();
    });
  },
  beforeUnmount() {
    clearInterval(this.animation);
  },
  methods: {
    play() {
      if (this.isPlaying) {
        this.isPlaying = false;
        clearInterval(this.animation);
      } else {
        this.isPlaying = true;

        this.animation = setInterval(() => {
          const chart = this.$refs.chart.chart;
          
          this.points = this.scale(this.points, this.scaleFactor, this.points[this.choosedPoint]);
          this.points = this.rotate(this.points, this.rotationFactor, this.points[this.choosedPoint]);

          let p1 = this.points[0];
          let p2 = this.points[1];
          let p3 = this.points[2];
          let p4 = this.points[3];

          this.chartData.datasets[0].data[0] = p1;
          this.chartData.datasets[0].data[1] = p2;
          this.chartData.datasets[0].data[2] = p3;
          this.chartData.datasets[0].data[3] = p4;
          this.chartData.datasets[0].data[4] = p1;
          chart.update();
        }, 100);
      }
    },
    scale(points, factor, center) {
      const scaledPoints = points.map(point => [
        (point[0] - center[0])*factor + center[0], 
        (point[1] - center[1])*factor + center[1]
      ]);

      return scaledPoints;
    },
    rotate(points, angle, center) {
      const radians = (Math.PI / 180) * angle;
      const cosTheta = Math.cos(radians);
      const sinTheta = Math.sin(radians);
      const rotatedPoints = points.map(point => [
        cosTheta * (point[0] - center[0]) + sinTheta * (point[1] - center[1]) + center[0],
        -sinTheta * (point[0] - center[0]) + cosTheta * (point[1] - center[1]) + center[1],
      ]);

      return rotatedPoints;
    },
    saveImage() {
      const chart = this.$refs.chart.chart;

      const imageData = chart.toBase64Image();

      const link = document.createElement('a');
      link.href = imageData;
      link.download = 'chart_image.png';

      link.click();
    },
  },
  watch: {
    points: {
      handler(newPoints) {
        if (newPoints.length === 3) {
          this.start = false;
          const p1 = this.points[0];
          const p2 = this.points[1];
          const p3 = this.points[2];
          const o = [p1[0]/2 + p3[0]/2, p1[1]/2 + p3[1]/2];
          const p4 = [o[0]*2 - p2[0], o[1]*2 - p2[1]];
          this.chartData.datasets[0].data.push(p4);
          this.chartData.datasets[0].data.push(p1);
          this.points.push(p4);
          this.$nextTick(() => {
            const chart = this.$refs.chart.chart;
            chart.zoom(-1000);
            chart.update();
          });
        }
      },
      deep: true,
    },
  },
};
</script>

<style scoped>
.btn-playpause {
  width: 60px;
  height: 45px;
  background-color: #ebebeb;
  border: 3px solid #ebebeb;
  border-radius: 12px;
  font-size: 28px;
  margin-top: 13px;
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
