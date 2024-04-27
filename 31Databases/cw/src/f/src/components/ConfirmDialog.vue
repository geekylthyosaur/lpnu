<template>
  <div class="modal">
    <div class="modal-content">
      <h2>Are you sure?</h2>
      <button @click="confirm" class="confirm-button">Confirm</button>
      <button @click="cancel" class="cancel-button">Cancel</button>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
    }
  },
  mounted() {
    window.addEventListener("keyup", (e) => {
      if (e.key === "Enter") {
        this.confirm();
      } else if (e.key === "Escape") {
        this.cancel();
      }
    });
  },
  beforeUnmount() {
    window.removeEventListener("keyup", (e) => {
      if (e.key === "Enter") {
        this.confirm();
      } else if (e.key === "Escape") {
        this.cancel();
      }
    });
  },
  methods: {
    confirm() {
      this.$emit("confirm");
    },
    cancel() {
      this.$emit("cancel");
    }
  }
}
</script>

<style scoped>
.modal {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.5);
  display: flex;
  justify-content: center;
  align-items: center;
  z-index: 9999;
}

.modal-content {
  background-color: white;
  padding: 20px;
  border-radius: 8px;
  width: 20%;
  text-align: center;
}

.confirm-button,
.cancel-button {
  width: 40%;
  padding: 10px;
  margin: 10px;
  color: white;
  border: none;
  border-radius: 4px;
  cursor: pointer;
}

.confirm-button {
  background-color: dodgerblue;
}

.cancel-button {
  background-color: gray;
}

.confirm-button:hover {
  background-color: royalblue;
}

.cancel-button:hover {
  background-color: dimgray;
}
</style>

