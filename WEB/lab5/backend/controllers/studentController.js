const Student = require('../models/student');

async function getAllStudents(req, res) {
  try {
    const students = await Student.find({});
    const formattedStudents = students.map(student => {
      const formattedBirthday = student.birthday.toISOString().slice(0, 10);
      return { ...student.toObject(), birthday: formattedBirthday };
    });
    res.send(formattedStudents);
  } catch (err) {
    console.log(err);
    res.status(500).send(err);
  }
}

async function getStudentById(req, res) {
  try {
    const student = await Student.findById(req.params.id);
    if (!student) {
      res.status(404).send();
    } else {
      const formattedBirthday = student.birthday.toISOString().slice(0, 10);

      res.json({ student: { ...student.toObject(), birthday: formattedBirthday } });
    }
  } catch (err) {
    console.log(err);
    res.status(500).send(err);
  }
}

async function createStudent(req, res) {
  try {
    const student = new Student({
      group: req.body.group,
      name: req.body.name,
      gender: req.body.gender,
      birthday: req.body.birthday,
      status: req.body.status,
    });
    await student.save();
    res.send(student);
  } catch (err) {
    console.log(err);
    res.status(500).send(err);
  }
}

async function updateStudent(req, res) {
  try {
    const student = await Student.findByIdAndUpdate(req.params.id, req.body, { new: true });
    if (!student) {
      res.status(404).send();
    } else {
      res.send(student);
    }
  } catch (err) {
    console.log(err);
    res.status(500).send(err);
  }
}

async function deleteStudent(req, res) {
  try {
    const student = await Student.findByIdAndDelete(req.params.id);
    if (!student) {
      res.status(404).send();
    } else {
      res.send(student);
    }
  } catch (err) {
    console.log(err);
    res.status(500).send(err);
  }
}

module.exports = {
  createStudent,
  getAllStudents,
  getStudentById,
  updateStudent,
  deleteStudent
};
