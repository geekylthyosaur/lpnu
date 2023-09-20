import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the n: ");
        int n = scanner.nextInt();
        Series series = new Series();
        try {
            Fraction result = series.calculate(n);
            System.out.printf("Result: " + result.toString());
        }
        catch (IllegalArgumentException e) {
            System.out.printf(e.toString());
        }
    }
}