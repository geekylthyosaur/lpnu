import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) throws Exception {
        var project = new Project("2023-10-01", "TODO", "My todo list");
        var task1 = new Task(new Deadline("2023-01-11"), Priority.Low, "Complete research report", "Gather data and create the report.");
        var task2 = new Task(new Deadline("2023-01-09"), Priority.Low, "Call client", "Discuss project updates and follow up.");
        var task3 = new Task(new Deadline("2023-01-09"), Priority.Low, "Write blog post", "Select a topic and start writing the post.");
        var task4 = new Task(new Deadline("2023-01-09"), Priority.Low, "Exercise", "Go for a run or hit the gym.");
        var task5 = new Task(new Deadline("2023-01-09"), Priority.Low, "Grocery shopping", "Buy groceries for the week.");
        var task6 = new Task(new Deadline("2023-01-17"), Priority.Low, "Plan weekend trip", "Research destinations and make an itinerary.");
        var task7 = new Task(new Deadline("2023-01-01"), Priority.Low, "Review budget", "Check monthly expenses and savings.");
        var task8 = new Task(new Deadline("2023-01-09"), Priority.Low, "Study for exam", "Review study materials for upcoming exam.");
        task1.addInnerTask(task2);
        task1.addInnerTask(task3);

        task3.addInnerTask(task7);
        task2.addInnerTask(task4);
        task2.addInnerTask(task5);
        task5.addInnerTask(task8);
        project.addTask(task1);
        System.out.println(project);
    }
}

enum Priority {
    High,
    Medium,
    Low;

    @Override
    public String toString() {
        return switch (this) {
            case High -> "High";
            case Medium -> "Medium";
            case Low -> "Low";
        };
    }
}

class Project {
    Deadline deadline;
    List<Task> tasks;
    String name;
    String description;
    Project(String deadline, String name, String description) {
        this.tasks = new ArrayList<>();
        this.deadline = new Deadline(deadline);
        this.name = name;
        this.description = description;
    }
    Deadline getDeadline() {
        Deadline deadline = null;
        for (var task : this.tasks) {
            if (deadline == null) {
                deadline = task.getDeadline();
            }
            if (task.getDeadline().compareTo(deadline) > 0) {
                deadline = task.getDeadline();
            }
        }
        return this.deadline;
    }
    String getName() {
        return this.name;
    }
    String getDescription() {
        return this.description;
    }
    void addTask(Task task) throws Exception {
        if (task.getDeadline().compareTo(getDeadline()) > 0) {
            throw new Exception("Invalid deadline");
        }
        this.tasks.add(task);
    }
    @Override
    public String toString() {
        StringBuilder format = new StringBuilder();
        format.append("PROJECT ").append(getName()).append(" - ").append(getDescription()).append("(Due ").append(getDeadline()).append(")\n");
        for (var task : this.tasks) {
            format.append("\t").append(task).append("\n");
        }
        return format.toString();
    }
}

class Task {
    Deadline deadline;
    Priority priority;
    List<Task> innerTasks;
    String name;
    String description;
    Task(Deadline deadline, Priority priority, String name, String description) {
        this.deadline = deadline;
        this.priority = priority;
        this.innerTasks = new ArrayList<>();
        this.name = name;
        this.description = description;
    }
    Deadline getDeadline() {
        var innerTasksDeadline = this.getInnerTasksDeadline();
        if (this.deadline.compareTo(innerTasksDeadline) > 0) {
            return this.deadline;
        } else {
            return innerTasksDeadline;
        }
    }
    Deadline getInnerTasksDeadline() {
        Deadline deadline = this.deadline;
        for (var task : this.innerTasks) {
            if (task.getDeadline().compareTo(deadline) > 0) {
                deadline = task.getDeadline();
            }
        }
        return this.deadline;
    }
    Priority getPriority() {
        return this.priority;
    }
    String getName() {
        return this.name;
    }
    String getDescription() {
        return this.description;
    }
    List<Task> getInnerTasks() {
        return this.innerTasks;
    }
    void addInnerTask(Task task) throws Exception {
        if (task.getDeadline().compareTo(getDeadline()) > 0) {
            throw new Exception("Invalid deadline");
        }
        this.innerTasks.add(task);
    }
    @Override
    public String toString() {
        return this.toString(1);
    }
    String toString(Integer i) {
        StringBuilder format = new StringBuilder();
        format.append("TASK").append(" <").append(getPriority()).append("> ").append(getName()).append(" (Due ").append(getDeadline()).append(")");
        if (!getInnerTasks().isEmpty()) {
            for (var task : this.getInnerTasks()) {
                format.append("\n").append(repeat(i, "\t")).append(task.toString(i + 1));
            }
        }
        return format.toString();
    }
    public static String repeat(int count, String with) {
        return new String(new char[count]).replace("\0", with);
    }
}

class Deadline implements Comparable<Deadline> {
    LocalDate date;
    Deadline(String str) {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        this.date = LocalDate.parse(str, formatter);
    }
    @Override
    public String toString() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        return this.date.format(formatter);
    }
    @Override
    public int compareTo(Deadline other) {
        return this.date.compareTo(other.date);
    }
}