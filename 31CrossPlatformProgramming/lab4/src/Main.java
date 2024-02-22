import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws Exception {
        var projects = new ArrayList<Project>();
        var help = "addTask/addProject/list/exit";

        Scanner scanner = new Scanner(System.in);
        System.out.println(help);

        var pr = new Project("2012-12-12", "q", "q");
        var task1 = new Task("2012-12-12", "low", "a", "a");
        var task2 = new Task("2012-12-12", "low", "b", "b");
        var task3 = new Task("2012-12-12", "low", "c", "c");
        var task4 = new Task("2012-12-12", "low", "d", "d");
        var task5 = new Task("2012-12-12", "low", "e", "e");
        task1.addInnerTask(task2);
        task2.addInnerTask(task4);
        task1.addInnerTask(task3);
        pr.addTask(task1);
        pr.addTask(task5);
        System.out.println(pr);

        while (true) {
            var input = scanner.nextLine();

            if (input.equalsIgnoreCase("addTask")) {
                System.out.println("Creating new task:");
                System.out.print("\tname: ");
                var name = scanner.nextLine();
                System.out.print("\tdescription: ");
                var description = scanner.nextLine();
                System.out.print("\tdeadline: ");
                var deadline = scanner.nextLine();
                System.out.print("\tpriority: ");
                var priority = scanner.nextLine();
                var task = new Task(deadline, priority, name, description);
                System.out.print("\tadd to: ");
                var taskName = scanner.nextLine();
                var project = findProject(taskName, projects);
                var inner = findInnerTask(taskName, projects);
                if (project != null) {
                    project.addTask(task);
                    System.out.println("Added new task: " + task);
                } else if (inner != null) {
                    inner.addInnerTask(task);
                    System.out.println("Added new task: " + task);
                } else {
                    System.out.println("Cannot add task");
                }
            } else if (input.equalsIgnoreCase("addProject")) {
                System.out.println("Creating new project:");
                System.out.print("\tname: ");
                var name = scanner.nextLine();
                System.out.print("\tdescription: ");
                var description = scanner.nextLine();
                System.out.print("\tdeadline: ");
                var deadline = scanner.nextLine();
                var project = new Project(deadline, name, description);
                projects.add(project);
                System.out.println("Added new project: " + project);
            } else if (input.equalsIgnoreCase("list")) {
                for (var p : projects) {
                    System.out.println(p);
                }
            } else if (input.equalsIgnoreCase("exit")) {
                break;
            }
        }
    }

    static Project findProject(String name, ArrayList<Project> projects) {
        for (var p : projects) {
            if (p.getName().equalsIgnoreCase(name)) {
                return p;
            }
        }
        return null;
    }
    static Task findInnerTask(String name, ArrayList<Project> projects) {
        for (var p : projects) {
            for (var t : p.tasks) {
                if (t.getName().equalsIgnoreCase(name)) {
                    return t;
                }
                var inner = t.findInnerTask(name);
                if (inner != null) {
                    return inner;
                }
            }
        }
        return null;
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
        format.append("[P] ").append(getName()).append(" - ").append(getDescription()).append(" (Due ").append(getDeadline()).append(")\n");
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
    Task(String deadline, String priority, String name, String description) {
        this.deadline = new Deadline(deadline);
        if (priority.equalsIgnoreCase("low")) {
            this.priority = Priority.Low;
        } else if (priority.equalsIgnoreCase("medium")) {
            this.priority = Priority.Medium;
        } else if (priority.equalsIgnoreCase("high")) {
            this.priority = Priority.High;
        }
        this.innerTasks = new ArrayList<>();
        this.name = name;
        this.description = description;
    }
    Task findInnerTask(String name) {
        for (var t : getInnerTasks()) {
            if (t.getName().equalsIgnoreCase(name)) {
                return t;
            }
            var inner = t.findInnerTask(name);
            if (inner != null) {
                return inner;
            }
        }
        return null;
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
        return this.toString(2);
    }
    String toString(Integer i) {
        StringBuilder format = new StringBuilder();
        format.append("[T]").append(" <").append(getPriority()).append("> ").append(getName()).append(" (Due ").append(getDeadline()).append(")");
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