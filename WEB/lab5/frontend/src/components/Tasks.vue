<template>
  <div class="container">
    <div class="row">
      <div class="col-sm-4">
        <h3>To Do</h3>
        <ul class="list-group">
          <li class="list-group-item" v-for="(todo, index) in filteredTodos('todo')" :key="todo._id">
            {{ todo.title }}
            <button class="btn btn-success btn-sm float-right" @click="moveToInProgress(index)">In Progress</button>
          </li>
        </ul>
        <div class="form-group">
          <input class="form-control" type="text" placeholder="Add new todo" v-model="newTodoTitle">
          <button class="btn btn-primary mt-2" @click="addTodo">Add Todo</button>
        </div>
      </div>
      <div class="col-sm-4">
        <h3>In Progress</h3>
        <ul class="list-group">
          <li class="list-group-item" v-for="(todo, index) in filteredTodos('inProgress')" :key="todo._id">
            {{ todo.title }}
            <button class="btn btn-success btn-sm float-right" @click="moveToDone(index)">Done</button>
            <button class="btn btn-warning btn-sm float-right mr-2" @click="moveToTodo(index)">To Do</button>
          </li>
        </ul>
      </div>
      <div class="col-sm-4">
        <h3>Done</h3>
        <ul class="list-group">
          <li class="list-group-item" v-for="(todo, index) in filteredTodos('done')" :key="todo._id">
            {{ todo.title }}
            <button class="btn btn-warning btn-sm float-right" @click="moveToInProgress(index)">In Progress</button>
            <button class="btn btn-danger btn-sm float-right mr-2" @click="removeTodo(index)">Remove</button>
          </li>
        </ul>
      </div>
    </div>
  </div>
</template>

<script>
  import axios from 'axios';

  export default {
    name: 'TasksComponent',
    data() {
      return {
        todos: [],
        newTodoTitle: '',
        todoId: 0,
      }
    },
    created() {
      axios.get('http://localhost:3000/tasks')
        .then(response => {
          this.todos = response.data;
          console.log(this.todos)
        })
        .catch(error => {
          console.log(error);
        });
    },
    methods: {
      addTodo() {
        if (this.newTodoTitle !== '') {
          const newTodo = {
            id: this.todoId++,
            title: this.newTodoTitle,
            state: 'todo',
          };

          axios.post('http://localhost:3000/tasks', newTodo)
            .then(response => {
              this.todos.push(response.data);
              this.newTodoTitle = '';
            })
            .catch(error => {
              console.log(error);
            });
        }
      },
      moveToInProgress(index) {
        const taskId = this.todos[index]._id;
        const updatedTask = { state: 'inProgress' };

        // Update the task state to inProgress on the server
        axios.put(`http://localhost:3000/tasks/${taskId}`, updatedTask)
          .then(() => {
            this.todos[index].state = 'inProgress';
          })
          .catch(error => {
            console.log(error);
          });
      },
      moveToDone(index) {
        const taskId = this.todos[index]._id;
        const updatedTask = { state: 'done' };

        // Update the task state to done on the server
        axios.put(`http://localhost:3000/tasks/${taskId}`, updatedTask)
          .then(() => {
            this.todos[index].state = 'done';
          })
          .catch(error => {
            console.log(error);
          });
      },
      moveToTodo(index) {
        const taskId = this.todos[index]._id;
        const updatedTask = { state: 'todo' };

        // Update the task state to todo on the server
        axios.put(`http://localhost:3000/tasks/${taskId}`, updatedTask)
          .then(() => {
            this.todos[index].state = 'todo';
          })
          .catch(error => {
            console.log(error);
          });
      },
      removeTodo(index) {
        const taskId = this.todos[index]._id;

        // Remove the task from the server
        axios.delete(`http://localhost:3000/tasks/${taskId}`)
          .then(() => {
            this.todos.splice(index, 1);
          })
          .catch(error => {
            console.log(error);
          });
      },
      filteredTodos(state) {
        return this.todos.filter(todo => todo.state === state);
      }
    }
  };
</script>

