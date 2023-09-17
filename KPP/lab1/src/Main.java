import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        var scanner = new Scanner(System.in);
        System.out.print("Enter n: ");
        var inputStr = scanner.nextLine();
        scanner.close();
        var input = Integer.parseInt(inputStr);
        var numerator = 1;
        var denumerator = 1;
        for (int n = 1; n <= input; n++) {
            denumerator *= n;
        }
        System.out.print("Result: " + numerator + "/" + denumerator);
    }
}