import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Events data = new Events();
        String filePath = "data.csv";
        try {
            FileReader fileReader = new FileReader(filePath);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                var event = new Event(line);
                data.add(event);
            }
            bufferedReader.close();
            fileReader.close();
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
        System.out.println("Before sorting:");
        System.out.println(data);
        data.sort();
        System.out.println("After sorting:");
        System.out.println(data);
    }
}

class Events {
    Map<Integer, List<Event>> data;
    Events() {
        this.data = new HashMap<>();
    }
    public void add(Event e) {
        var key = e.date.year;
        this.data.putIfAbsent(key, new ArrayList<>());
        this.data.get(key).add(e);
    }
    public void sort() {
        this.data.values().forEach(Collections::sort);
    }
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        for (Map.Entry<?, ?> entry : this.data.entrySet()) {
            sb.append(entry.getKey())
                    .append(":")
                    .append(entry.getValue())
                    .append(",\n");
        }

        if (!this.data.isEmpty()) {
            sb.setLength(sb.length() - 2);
        }

        return sb.toString();
    }
}

class Event implements Comparable<Event> {
    String name;
    Date date;
    Event(String s) {
        var items = s.split(",");
        this.name = items[0];
        var year = Integer.parseInt(items[1]);
        var month = Integer.parseInt(items[2]);
        var day = Integer.parseInt(items[3]);

        this.date = new Date(year, month, day);
    }
    @Override
    public String toString() {
        return "{" + '"' + this.name + '"' + ", " + this.date + "}";
    }
    @Override
    public int compareTo(Event other) {
        return this.date.compareTo(other.date);
    }
}

class Date implements Comparable<Date> {
    int year;
    int month;
    int day;
    Date(int year, int month, int day) {
        this.year = year;
        this.month = month;
        this.day = day;
    }
    @Override
    public String toString() {
        return this.year + "-" + this.month + "-" + this.day;
    }
    @Override
    public int compareTo(Date other) {
        if (this.year != other.year) {
            return Integer.compare(this.year, other.year);
        }
        if (this.month != other.month) {
            return Integer.compare(this.month, other.month);
        }
        return Integer.compare(this.day, other.day);
    }
}