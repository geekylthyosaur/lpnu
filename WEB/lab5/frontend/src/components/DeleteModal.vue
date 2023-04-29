<template>
  <button @click="openModal" class="btn btn-danger">Delete</button>

  <div class="modal fade" tabindex="-1" role="dialog" :class="{ 'show': showModal }">
    <div class="modal-dialog" role="document">
      <div class="modal-content">
        <div class="modal-header">
          <h5 class="modal-title" id="deleteStudentModalLabel">Delete Student</h5>
          <button type="button" class="close" data-dismiss="modal" aria-label="Close">
            <span aria-hidden="true">&times;</span>
          </button>
        </div>
        <div class="modal-body">
          <p>Are you sure you want to delete this student?</p>
        </div>
        <div class="modal-footer">
          <button type="button" class="btn btn-secondary" @click="closeModal">Cancel</button>
          <button type="button" class="btn btn-danger" @click="deleteStudent">Delete</button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: "DeleteStudentModal",
  data() {
    return {
      showModal: false,
    };
  },
  props: {
    student: {
      type: Object,
      required: true,
    },
  },
  methods: {
    openModal() {
      this.showModal = true
      document.body.classList.add('modal-open')
    },
    closeModal() {
      this.showModal = false
      document.body.classList.remove('modal-open')
    },
    deleteStudent() {
      this.$emit("deleteStudent", this.student.id);
      this.closeModal();
    },
  },
};
</script>

<style scoped>
  .modal {
    display: none;
  }

  .modal.show {
    display: block;
  }
</style>
