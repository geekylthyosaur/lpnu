<template>
  <div>
    <button @click="openModal" class="btn btn-primary">Add</button>

    <div class="modal fade" tabindex="-1" role="dialog" :class="{ 'show': showModal }">
      <div class="modal-dialog modal-dialog-centered" role="document">
        <div class="modal-content">
          <div class="modal-header">
            <h5 class="modal-title">Add Student</h5>
            <button type="button" class="close" @click="closeModal">
              <span>&times;</span>
            </button>
          </div>
          <div class="modal-body">
            <form>
              <div class="form-group">
                <label for="group">Group</label>
                <input type="text" class="form-control" id="group" v-model="group">
              </div>
              <div class="form-group">
                <label for="name">Name</label>
                <input type="text" class="form-control" id="name" v-model="name">
              </div>
              <div class="form-group">
                <label for="gender">Gender</label>
                <select class="form-control" id="gender" v-model="gender">
                  <option value="male">Male</option>
                  <option value="female">Female</option>
                </select>
              </div>
              <div class="form-group">
                <label for="birthday">Birthday</label>
                <input type="date" class="form-control" id="birthday" v-model="birthday">
              </div>
            </form>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-secondary" @click="closeModal">Close</button>
            <button type="button" class="btn btn-primary" @click="createStudent">Create</button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  export default {
    name: 'AddStudentModal',
    data() {
      return {
        showModal: false,
        group: '',
        name: '',
        gender: 'male',
        birthday: ''
      }
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
      createStudent() {
        const student = {
          group: this.group,
          name: this.name,
          gender: this.gender,
          birthday: this.birthday
        }
        this.$emit('studentCreated', student)
        this.closeModal()
      }
    }
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
