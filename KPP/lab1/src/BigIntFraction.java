import java.math.BigInteger;

public class BigIntFraction implements Fraction<BigIntFraction> {
    private BigInteger numerator;
    private BigInteger denominator;

    public BigIntFraction(BigInteger numerator, BigInteger denominator) {
        this.numerator = numerator;
        this.denominator = denominator;
    }
    @Override
    public BigIntFraction add(BigIntFraction other) {
        BigInteger newNumerator = this.numerator.multiply(other.denominator)
                .add(other.numerator.multiply(this.denominator));
        BigInteger newDenominator = this.denominator.multiply(other.denominator);
        BigIntFraction newFraction = new BigIntFraction(newNumerator, newDenominator);
        newFraction.reduce();
        return newFraction;
    }

    @Override
    public void reduce() {
        BigInteger n = this.numerator;
        BigInteger d = this.denominator;
        while(!d.equals(new BigInteger("0"))) {
            BigInteger t = d;
            d = n.remainder(d);
            n = t;
        }
        this.numerator = this.numerator.divide(n);
        this.denominator = this.denominator.divide(n);
    }

    public String toString() {
        return this.numerator.toString() + "/" + this.denominator.toString();
    }
}
