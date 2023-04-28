<template>
  <div>
    <div class="container-fluid mt-4">
      <div class="row">
        <div class="col-md-6">
          <h3>Students</h3>
        </div>
        <div class="col-md-6 d-flex justify-content-end">
          <add-modal @studentCreated="addStudent"/>
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
            <td>{{ student.birthday }}</td>
            <td>
              <span class="badge bg-success"></span>
            </td>
            <td>
              <div class="d-flex justify-content-start">
                <edit-modal :student="student" @studentUpdated="updateStudent"/>
                <delete-modal :student="student" @deleteStudent="deleteStudent"/>
              </div>
            </td>
          </tr>
        </tbody>
      </table>
    </div>
  </div>
</template>

<script>
  import AddStudentModal from './AddStudent.vue'
  import EditStudentModal from './EditStudent.vue'
  import DeleteStudentModal from './DeleteStudent.vue'

  export default {
    name: 'StudentsTable',
    components: {
      'add-modal': AddStudentModal,
      'edit-modal': EditStudentModal,
      'delete-modal': DeleteStudentModal,
    },
    data() {
      return {
        students: [],
        selectedStudents: [],
      }
    },
    methods: {
      selectAll() {
        if (this.selectedStudents.length === this.students.length) {
          this.selectedStudents = []
        } else {
          this.selectedStudents = this.students.map(student => student.id)
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
      addStudent(student) {
        this.students.push(student);
      },
      updateStudent(updatedStudent) {
        const index = this.students.findIndex(student => student.id === updatedStudent.id)
        if (index !== -1) {
          this.students.splice(index, 1, updatedStudent)
        }
      },
      deleteStudent(studentId) {
        console.log(studentId);
      },
    }
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
