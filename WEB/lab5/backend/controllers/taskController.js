const Task = require('../models/task');

async function createTask(req, res) {
  const { title, state } = req.body;
  const task = new Task({ title, state });
  console.log('Adding task', task);
  try {
    const savedTask = await task.save();
    res.status(201).json(savedTask);
  } catch (err) {
    console.error(err);
    res.status(500).send('Server Error');
  }
}

async function getAllTasks(req, res) {
  try {
    const tasks = await Task.find();
    console.log('Getting tasks', tasks);
    res.json(tasks);
  } catch (err) {
    console.error(err);
    res.status(500).send('Server Error');
  }
}

async function updateTask(req, res) {
  const { id } = req.params;
  const { title, state } = req.body;

  try {
    const task = await Task.findById(id);
    if (!task) {
      return res.status(404).json({ error: 'Task not found' });
    }

    if (title) {
      task.title = title;
    }

    if (state) {
      task.state = state;
    }

    console.log('Updating task', task);
    const updatedTask = await task.save();
    res.json(updatedTask);
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: 'Server error' });
  }
}

async function deleteTask(req, res) {
  const { id } = req.params;

  try {
    const task = await Task.findById(id);
  console.log('Deleting task', task);
    if (!task) {
      return res.status(404).json({ error: 'Task not found' });
    }

    await task.deleteOne();
    res.json({ message: 'Task deleted successfully' });
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: 'Server error' });
  }
}

module.exports = {
  createTask,
  getAllTasks,
  updateTask,
  deleteTask,
};
