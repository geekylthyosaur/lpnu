import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.stream.Collectors;

class Book {
    String author;
    String title;
    int year;

    public Book(String author, String title, int year) {
        this.author = author;
        this.title = title;
        this.year = year;
    }

    int getYear() {
        return this.year;
    }

    @Override
    public String toString() {
        return "Book {" +
                "author='" + author + '\'' +
                ", title='" + title + '\'' +
                ", year=" + year +
                "}\n";
    }
}

class Subscription {
    String lastName;
    String firstName;
    String email;

    public Subscription(String lastName, String firstName, String email) {
        this.lastName = lastName;
        this.firstName = firstName;
        this.email = email;
    }

    @Override
    public String toString() {
        return "Subscription{" +
                "lastName='" + lastName + '\'' +
                ", firstName='" + firstName + '\'' +
                ", email='" + email + '\'' +
                '}';
    }
    // Getters and setters if needed
}

class BorrowedBook {
    String author;
    String title;
    int year;
    Date borrowDate;
    Date plannedReturnDate;
    Date actualReturnDate;

    public BorrowedBook(String author, String title, int year, Date borrowDate, Date plannedReturnDate, Date actualReturnDate) {
        this.author = author;
        this.title = title;
        this.year = year;
        this.borrowDate = borrowDate;
        this.plannedReturnDate = plannedReturnDate;
        this.actualReturnDate = actualReturnDate;
    }

    @Override
    public String toString() {
        return "BorrowedBook{" +
                "author='" + author + '\'' +
                ", title='" + title + '\'' +
                ", year=" + year +
                ", borrowDate=" + borrowDate +
                ", plannedReturnDate=" + plannedReturnDate +
                ", actualReturnDate=" + actualReturnDate +
                '}';
    }
    // Getters and setters if needed
}
class Reader {
    Subscription subscription;
    List<BorrowedBook> borrowedBooks;
    Date actualReturnDate;
    Date plannedReturnDate;
    public Reader(Subscription subscription, List<BorrowedBook> borrowedBooks) {
        this.subscription = subscription;
        this.borrowedBooks = borrowedBooks;
    }

    @Override
    public String toString() {
        return "Reader{" +
                "subscription=" + subscription +
                ", \n\tborrowedBooks=" + borrowedBooks +
                "}\n";
    }
    // Getters and setters if needed
}

class Library {
    List<Book> allBooks;
    List<Reader> allReaders;

    public Library(List<Book> allBooks, List<Reader> allReaders) {
        this.allBooks = allBooks;
        this.allReaders = allReaders;
    }

    // Task 1: Sort all books by the year of publication
    public List<Book> sortBooksByYear() {
        return allBooks.stream().sorted(Comparator.comparingInt(Book::getYear)).collect(Collectors.toList());
    }

    // Task 2: Create a list of addresses for heavy readers
    public List<String> getAddressesForHeavyReaders() {
        return allReaders.stream()
                .filter(reader -> reader.borrowedBooks.size() > 2)
                .map(reader -> reader.subscription.email)
                .collect(Collectors.toList());
    }

    // Task 3: Check how many users took books from a specified author
    public long countUsersByAuthor(String author) {
        return allReaders.stream()
                .flatMap(reader -> reader.borrowedBooks.stream())
                .filter(book -> book.author.equals(author))
                .count();
    }

    // Task 4: Find the maximum number of books taken by a reader
    public int getMaxBooksTakenByReader() {
        return allReaders.stream()
                .mapToInt(reader -> reader.borrowedBooks.size())
                .max()
                .orElse(0);
    }

    // Task 5: Send different messages to two groups of users
    public void sendMessagesToUsers() {
        List<Reader> group1 = allReaders.stream()
                .filter(reader -> reader.borrowedBooks.size() < 2)
                .toList();

        List<Reader> group2 = allReaders.stream()
                .filter(reader -> reader.borrowedBooks.size() >= 2)
                .toList();

        // Implement sending messages to each group
        System.out.println("Group 1: Notify about new library arrivals");
        group1.forEach(reader -> System.out.println("Message to " + reader.subscription.email + ": New library arrivals"));

        System.out.println("\nGroup 2: Remind about timely book returns");
        group2.forEach(reader -> System.out.println("Message to " + reader.subscription.email + ": Return books on time"));
    }

    // Task 6: Create a list of debtors and their overdue books
    public Map<Reader, List<BorrowedBook>> getDebtors() {
        Date currentDate = new Date();

        return allReaders.stream()
                .filter(reader -> reader.actualReturnDate == null || reader.actualReturnDate.after(reader.plannedReturnDate))
                .collect(Collectors.toMap(
                        reader -> reader,
                        reader -> reader.borrowedBooks.stream()
                                .filter(borrowedBook ->
                                        borrowedBook.actualReturnDate == null ||
                                                borrowedBook.actualReturnDate.after(borrowedBook.plannedReturnDate))
                                .collect(Collectors.toList())
                ));
    }

    // New method to parse borrowed book data
    private BorrowedBook parseBorrowedBook(String[] data) throws ParseException {
        String readerEmail = data[1];
        Reader reader = allReaders.stream()
                .filter(r -> r.subscription.email.equals(readerEmail))
                .findFirst()
                .orElseThrow(() -> new IllegalArgumentException("Reader not found for borrowed book entry."));

        String author = data[2];
        String title = data[3];
        int year = Integer.parseInt(data[4]);

        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        Date borrowDate = sdf.parse(data[5]);
        Date plannedReturnDate = data[6].isEmpty() ? null : sdf.parse(data[6]);
        Date actualReturnDate = data[7].isEmpty() ? null : sdf.parse(data[7]);

        return new BorrowedBook(author, title, year, borrowDate, plannedReturnDate, actualReturnDate);
    }


    // New method to read borrowed book entries from file
    List<BorrowedBook> readBorrowedBooksFromFile(String filePath) {
        List<BorrowedBook> borrowedBooks = new ArrayList<>();
        Reader currentReader = null;

        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] data = line.split(",");
                if ("Reader".equals(data[0])) {
                    if (currentReader != null) {
                        allReaders.add(currentReader);
                    }
                    currentReader = new Reader(new Subscription(data[1], data[2], data[3]), new ArrayList<>());
                } else if ("BorrowedBook".equals(data[0]) && currentReader != null) {
                    BorrowedBook borrowedBook = parseBorrowedBook(data);
                    currentReader.borrowedBooks.add(borrowedBook);
                    borrowedBooks.add(borrowedBook);
                }
                // Add more conditions for other types of data if needed
            }
            // Add the last reader to the list
            if (currentReader != null) {
                allReaders.add(currentReader);
            }
        } catch (IOException | ParseException e) {
            e.printStackTrace();
        }

        return borrowedBooks;
    }
}

public class Main {
    public static void main(String[] args) {
        List<Book> allBooks = new ArrayList<>();
        List<Reader> allReaders = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader("./src/library_data.txt"))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] data = line.split(",");
                if ("Book".equals(data[0])) {
                    allBooks.add(new Book(data[1], data[2], Integer.parseInt(data[3])));
                } else if ("Reader".equals(data[0])) {
                    allReaders.add(new Reader(new Subscription(data[1], data[2], data[3]), new ArrayList<>()));
                }
                // Add more conditions for other types of data if needed
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        Library library = new Library(allBooks, allReaders);

        library.readBorrowedBooksFromFile("./src/library_data.txt");

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\nSelect a task to perform:");
            System.out.println("1. Sort all books by the year of publication");
            System.out.println("2. Create a list of addresses for heavy readers");
            System.out.println("3. Check how many users took books from a specified author");
            System.out.println("4. Find the maximum number of books taken by a reader");
            System.out.println("5. Send messages to users");
            System.out.println("6. List of debtors and overdue books");
            System.out.println("0. Exit");

            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline character

            switch (choice) {
                case 1:
                    System.out.println("Task 1: Sorted books by year: \n" + library.sortBooksByYear());
                    break;
                case 2:
                    System.out.println("Task 2: Addresses for heavy readers: " + library.getAddressesForHeavyReaders());
                    break;
                case 3:
                    System.out.print("Enter author name: ");
                    String authorName = scanner.nextLine();
                    System.out.println("Task 3: Users who took books from " + authorName + ": " + library.countUsersByAuthor(authorName));
                    break;
                case 4:
                    System.out.println("Task 4: Maximum number of books taken by a reader: " + library.getMaxBooksTakenByReader());
                    break;
                case 5:
                    System.out.println("Task 5: Sending messages to users: \n");
                    library.sendMessagesToUsers();
                    break;
                case 6:
                    System.out.println("Task 6: List of debtors and overdue books: \n" + library.getDebtors());
                    break;
                case 0:
                    System.out.println("Exiting the program.");
                    System.exit(0);
                default:
                    System.out.println("Invalid choice. Please enter a valid option.");
            }
        }
    }
}
