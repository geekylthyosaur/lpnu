<template>
  <div>
    <error-modal v-if="error" @ok="closeError" showModal/>
    <div class="container-fluid mt-4">
      <div class="row">
        <div class="col-md-6">
          <h3 class="ml-5">Students</h3>
        </div>
        <div class="col-md-6 d-flex justify-content-end">
          <add-modal @studentCreated="addStudent" class="mr-5"/>
        </div>
      </div>
      <table class="table">
        <thead>
          <tr>
            <th>
              <input type="checkbox" @click="selectAll">
            </th>
            <th>Group</th>
            <th>Name</th>
            <th>Gender</th>
            <th>Birthday</th>
            <th>Status</th>
            <th>Options</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="(student, index) in students" :key="index">
            <td>
              <input type="checkbox" :checked="selectedStudents.includes(student.id)" @change="toggleSelection(student.id)">
            </td>
            <td>{{ student.group }}</td>
            <td>{{ student.name }}</td>
            <td>{{ student.gender }}</td>
            <td>{{ new Date(student.birthday).toDateString() }}</td>
            <td>
              <span class="badge bg-success"></span>
            </td>
            <td>
              <div class="d-flex justify-content-start">
                <edit-modal :student="student" @studentUpdated="updateStudent" class="mr-1"/>
                <delete-modal :student="student" @deleteStudent="deleteStudent(student._id)" class="ml-1"/>
              </div>
            </td>
          </tr>
        </tbody>
      </table>
    </div>
  </div>
</template>

<script>
  import AddStudentModal from './AddModal.vue'
  import EditStudentModal from './EditModal.vue'
  import DeleteStudentModal from './DeleteModal.vue'
  import ErrorModal from './ErrorModal.vue'
  import axios from 'axios'

  const instance = axios.create({
    baseURL: 'http://127.0.0.1:3000',
  });

  export default {
    name: 'StudentsTable',
    components: {
      'add-modal': AddStudentModal,
      'edit-modal': EditStudentModal,
      'delete-modal': DeleteStudentModal,
      'error-modal': ErrorModal,
    },
    data() {
      return {
        students: [],
        selectedStudents: [],
        error: false,
      }
    },
    mounted() {
      this.fetchStudents();
    },
    methods: {
      selectAll() {
        if (this.selectedStudents.length === this.students.length) {
          this.selectedStudents = []
        } else {
          this.selectedStudents = this.students.map(student => student._id)
        }
      },
      toggleSelection(studentId) {
        const index = this.selectedStudents.indexOf(studentId)
        if (index === -1) {
          this.selectedStudents.push(studentId)
        } else {
          this.selectedStudents.splice(index, 1)
        }
      },
      fetchStudents() {
        instance.get('/students')
          .then(response => {
            this.students = response.data;
          })
          .catch(error => {
            this.error = true;
            console.log(error);
          })
      },
      addStudent(student) {
        instance.post('/students', student)
          .then(response => {
            this.students.push(response.data);
          })
          .catch(error => {
            this.error = true;
            console.log(error);
          });
      },
      updateStudent(student) {
        instance.put(`/students/${student._id}`, student)
          .then(response => {
            const index = this.students.findIndex(student => student._id === response.data._id)
            if (index !== -1) {
              this.students.splice(index, 1, response.data)
            }
          })
          .catch(error => {
            this.error = true;
            console.log(error);
          });
      },
      deleteStudent(studentId) {
        instance.delete(`/students/${studentId}`)
          .then(() => {
            const index = this.students.findIndex(student => student._id === studentId)
            if (index !== -1) {
              this.students.splice(index, 1)
            }
          })
          .catch(error => {
            this.error = true;
            console.log(error);
          });
      },
    },
  }
</script>

<style scoped>
.badge.bg-success {
  background-color: lightgreen;
  border-radius: 50%;
  width: 20px;
  height: 20px;
  display: inline-flex;
  justify-content: center;
  align-items: center;
  color: #fff;
  text-align: center;
  font-size: 12px;
  font-weight: bold;
}

.badge.bg-secondary {
  background-color: lightgray;
  border-radius: 50%;
  width: 20px;
  height: 20px;
  display: inline-flex;
  justify-content: center;
  align-items: center;
  color: #fff;
  text-align: center;
  font-size: 12px;
  font-weight: bold;
}
</style>
