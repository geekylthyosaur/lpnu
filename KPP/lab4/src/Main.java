import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws Exception {
        var projects = new ArrayList<>();
        var help = "addTask/addProject/list/exit";

        Scanner scanner = new Scanner(System.in);
        System.out.println(help);

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
                System.out.print(task);
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
                System.out.print("Added new project: " + project);
            } else if (input.equalsIgnoreCase("list")) {
                System.out.print(projects);
            } else if (input.equalsIgnoreCase("exit")) {
                break;
            }
        }
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