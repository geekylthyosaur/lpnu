public class IntFraction implements Fraction<IntFraction>{
    private int numerator;
    private int denominator;

    public IntFraction(int numerator, int denominator) {
        this.numerator = numerator;
        this.denominator = denominator;
    }

    @Override
    public IntFraction add(IntFraction other) {
        int newNumerator = this.numerator * other.denominator + other.numerator * this.denominator;
        int newDenominator = this.denominator * other.denominator;
        IntFraction newFraction = new IntFraction(newNumerator, newDenominator);
        newFraction.reduce();
        return newFraction;
    }

    @Override
    public void reduce() {
        int n = this.numerator;
        int d = this.denominator;
        while(d != 0) {
            int t = d;
            d = n % d;
            n = t;
        }
        this.numerator /= n;
        this.denominator /= n;
    }

    @Override
    public String toString() {
        return this.numerator + "/" + this.denominator;
    }
}