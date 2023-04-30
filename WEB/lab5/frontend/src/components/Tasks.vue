<template>
  <div class="container">
    <div class="row">
      <div class="col-sm-4">
        <h3>To Do</h3>
        <ul class="list-group">
          <li class="list-group-item" v-for="(todo, index) in filteredTodos('todo')" :key="todo.id">
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
          <li class="list-group-item" v-for="(todo, index) in filteredTodos('inProgress')" :key="todo.id">
            {{ todo.title }}
            <button class="btn btn-success btn-sm float-right" @click="moveToDone(index)">Done</button>
            <button class="btn btn-warning btn-sm float-right mr-2" @click="moveToTodo(index)">To Do</button>
          </li>
        </ul>
      </div>
      <div class="col-sm-4">
        <h3>Done</h3>
        <ul class="list-group">
          <li class="list-group-item" v-for="(todo, index) in filteredTodos('done')" :key="todo.id">
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
export default {
  name: 'TasksCompoenent',
  data() {
    return {
      todos: [],
      newTodoTitle: '',
      todoId: 0,
    }
  },
  methods: {
    addTodo() {
      this.todos.push({
        id: this.todoId++,
        title: this.newTodoTitle,
        status: 'todo'
      });
      this.newTodoTitle = '';
    },
    moveToInProgress(index) {
      this.todos[index].status = 'inProgress';
    },
    moveToDone(index) {
      this.todos[index].status = 'done';
    },
    moveToTodo(index) {
      this.todos[index].status = 'todo';
    },
    removeTodo(index) {
      this.todos.splice(index, 1);
    },
    filteredTodos(status) {
      return this.todos.filter(todo => todo.status === status);
    }
  }
};
</script>

