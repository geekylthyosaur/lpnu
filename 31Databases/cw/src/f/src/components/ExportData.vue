<template>
  <div>
    <button @click="downloadJson"  class="download-btn">Export `{{ this.table }}` data</button>
  </div>
</template>

<script>
import axios from 'axios';

export default {
  props: {
    table: {
      type: String,
      required: true
    }
  },
  methods: {
    async downloadJson() {
      try {
        const response = await axios.get(`http://localhost:8080/${this.table}`, {
          responseType: 'blob' // To get binary data
        });
        const url = window.URL.createObjectURL(new Blob([response.data]));
        const link = document.createElement('a');
        link.href = url;
        link.setAttribute('download', 'data.json');
        document.body.appendChild(link);
        link.click();
      } catch (error) {
        console.error('Error downloading JSON:', error);
      }
    }
  }
};
</script>

<style scoped>
.container {
  text-align: center;
}

.download-btn {
  padding: 10px 20px;
  font-size: 16px;
  background-color: #007bff;
  color: #fff;
  border: none;
  border-radius: 5px;
  cursor: pointer;
  transition: background-color 0.3s ease;
}

.download-btn:hover {
  background-color: #0056b3;
}
</style>

