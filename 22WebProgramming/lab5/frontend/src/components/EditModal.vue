<template>
  <div>
    <button @click="openModal" class="btn btn-primary">Edit</button>
    <div class="modal fade" tabindex="-1" role="dialog" :class="{ 'show': showModal }">
      <div class="modal-dialog modal-dialog-centered" role="document">
        <div class="modal-content">
          <div class="modal-header">
            <h5 class="modal-title">Edit Student</h5>
            <button type="button" class="close" @click="closeModal">
              <span>&times;</span>
            </button>
          </div>
          <div class="modal-body">
            <form>
              <div class="form-group">
                <label for="group">Group</label>
                <input type="text" class="form-control" id="group" v-model="group" v-bind:class="{ 'is-invalid': Object.values(validationErrors).includes('group') }">
              </div>
              <div class="form-group">
                <label for="name">Name</label>
                <input type="text" class="form-control" id="name" v-model="name" v-bind:class="{ 'is-invalid': Object.values(validationErrors).includes('name') }">
              </div>
              <div class="form-group">
                <label for="gender">Gender</label>
                <select class="form-control" id="gender" v-model="gender" v-bind:class="{ 'is-invalid': Object.values(validationErrors).includes('gender') }">
                  <option value="male">Male</option>
                  <option value="female">Female</option>
                </select>
              </div>
              <div class="form-group">
                <label for="birthday">Birthday</label>
                <input type="date" class="form-control" id="birthday" v-model="birthday" v-bind:class="{ 'is-invalid': Object.values(validationErrors).includes('birthday') }">
              </div>
            </form>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-secondary" @click="closeModal">Close</button>
            <button type="button" class="btn btn-primary" @click="updateStudent">Save</button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
<script>
  export default {
    name: 'EditStudentModal',
    props: {
      student: {
        type: Object,
        required: true
      }
    },
    data() {
      return {
        showModal: false,
        validationErrors: [],
        group: '',
        name: '',
        gender: '',
        birthday: new Date(),
      }
    },
    mounted() {
      this.group = this.student.group;
      this.name = this.student.name;
      this.gender = this.student.gender;
      this.birthday = new Date(this.student.birthday).toISOString().slice(0,10);
    },
    methods: {
      openModal() {
        this.showModal = true;
        document.body.classList.add('modal-open');
      },
      closeModal() {
        this.showModal = false;
        document.body.classList.remove('modal-open');
      },
      updateStudent() {
        const student = {
          _id: this.student._id,
          group: this.group,
          name: this.name,
          gender: this.gender,
          birthday: new Date(this.birthday),
        }
        this.validationErrors = Object.keys(this.validateStudent(student));
        if (!Object.keys(this.validationErrors).length) {
          this.$emit('studentUpdated', student)
          this.closeModal()
        }
      },
      validateStudent(student) {
        const errors = {};

        if (!student.group || student.group.trim() === '') {
          errors.group = 'Group is required.';
        }

        if (!student.name || student.name.trim() === '') {
          errors.name = 'Name is required.';
        }

        if (!student.gender || (student.gender !== 'male' && student.gender !== 'female')) {
          errors.gender = 'Gender is required and must be either "male" or "female".';
        }

        if (!student.birthday) {
          errors.birthday = 'Birthday is required.';
        } else {
          const today = new Date();
          const birthdate = new Date(student.birthday);
          var age = today.getFullYear() - birthdate.getFullYear();
          const monthDiff = today.getMonth() - birthdate.getMonth();

          if (monthDiff < 0 || (monthDiff === 0 && today.getDate() < birthdate.getDate())) {
            age--;
          }

          if (age < 18) {
            errors.birthday = 'Must be 18 years or older to enroll.';
          }
        }

        return errors;
      },
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
