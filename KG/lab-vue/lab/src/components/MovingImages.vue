<template>
  <div v-if="start" class="d-flex" style="height: 540px; width: 800px;">
    <div class="d-flex justify-content-center align-items-center" style="width: 400px; height: 400px;">
      <canvas ref="chartCanvas" height="400px" width="400px"></canvas>
    </div>
  </div>
  <div v-if="!start" class="d-flex" style="height: 540px; width: 800px;">
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
          <canvas ref="chartCanvas" height="400px" width="400px"></canvas>
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
import Chart from 'chart.js/auto';
import zoomPlugin from 'chartjs-plugin-zoom';
import { getRelativePosition } from 'chart.js/helpers';
import { shallowRef } from 'vue';

export default {
  name: 'MovingImages',
  data() {
    return {
      start: true,
      chart: null,
      data: shallowRef([]),
      clickCoordinates: [],
    };
  },
  mounted() {
    Chart.register(zoomPlugin);
    this.initializeChart();
  },
  methods: {
    initializeChart() {
      const ctx = this.$refs.chartCanvas.getContext('2d');

      this.chart = new Chart(ctx, {
        type: 'scatter',
        data: {
          datasets: [
            {
              label: 'Math Chart',
              data: this.data,
              borderColor: 'rgba(75, 192, 192, 1)',
              backgroundColor: 'rgba(75, 192, 192, 0.2)',
            },
          ],
        },
        options: {
          responsive: true,
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
            zoom: {
              pan: {
                enabled: true,
                mode: 'xy',
              },
              zoom: {
                wheel: {
                  enabled: true,
                },
                pinch: {
                  enabled: true,
                },
                mode: 'xy',
              },
            },
          },
          onClick: (e) => {
            const canvasPosition = getRelativePosition(e, this.chart);
            const x = this.chart.scales.x.getValueForPixel(canvasPosition.x);
            const y = this.chart.scales.y.getValueForPixel(canvasPosition.y);
            this.data.push({x, y});
          },
        },
      });
    },
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
