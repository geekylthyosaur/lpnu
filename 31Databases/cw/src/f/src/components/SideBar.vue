<template>
  <div class="sidebar">
    <div v-for="(button, index) in buttons" :key="index">
      <button @click="click(index)" class="sidebar-button" :class="{ 'selected' : index === selected }">{{ button }}</button>
    </div>
  </div>
</template>

<script>
export default {
  props: {
    buttons: {
      type: Array,
      required: true,
    },
  },
  data() {
    return {
      selected: 0,
    };
  },
  methods: {
    click(index) {
      this.selected = index;
      this.$emit("click" + index);
    },
  },
};
</script>

<style scoped>
.sidebar {
  background-color: black;
  padding: 10px;
  position: fixed;
  top: 60px;
  width: 20%;
  height: 93%;
}

.sidebar-button {
  display: block;
  width: 80%;
  margin-left: 10%;
  margin-right: 10%;
  margin-bottom: 10px;
  padding: 8px;
  background-color: dodgerblue;
  color: #fff;
  border: none;
  cursor: pointer;
  border-radius: 5px;
  transition: background-color 0.3s ease, color 0.3s ease;
}

.sidebar-button:hover {
  background-color: royalblue;
}

.selected {
  background-color: white;
  color: black;
}

.selected:hover {
  background-color: lightgray;
}
</style>

