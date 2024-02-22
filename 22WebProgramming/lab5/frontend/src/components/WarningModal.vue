<template>
  <div>
    <div class="modal fade" tabindex="-1" role="dialog" v-bind:class="{ 'show': showModal }">
      <div class="modal-dialog modal-dialog-centered" role="document">
        <div class="modal-content">
          <div class="modal-header">
            <h5 class="modal-title">Warning</h5>
            <button type="button" class="close" @click="closeModal">
              <span>&times;</span>
            </button>
          </div>
          <div class="modal-body">
            <p>{{ warningMessage }}</p>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-secondary" @click="closeModal">Close</button>
            <button type="button" class="btn btn-secondary" @click="submitModal">Ok</button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  export default {
    name: 'WarningModal',
    props: {
      showModal: {
        type: Boolean,
        required: true,
      },
      warningMessage: {
        type: String,
        required: true,
      },
    },
    methods: {
      closeModal() {
        document.body.classList.remove('modal-open')
      },
      cancelModal() {
        this.closeModal();
        this.$emit('cancel');
      },
      okModal() {
        this.closeModal();
        this.$emit('ok');
      },
    },
  }
</script>

<style scoped>
  .modal {
    display: none;
  }

  .modal.show {
    display: block;
  }
</style>

