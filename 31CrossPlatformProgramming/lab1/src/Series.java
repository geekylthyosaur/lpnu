import java.math.BigInteger;

public class Series {
    public static Fraction calculate(int n) {
        if (n < 1) {
            throw new IllegalArgumentException("n should be greater than zero");
        }
        if (n < 16) {
            IntFraction fraction = new IntFraction(1, 1);
            for (int i = 2; i <= n; i++) {
                fraction = fraction.add(new IntFraction(1, i));
            }
            return fraction;
        }
        else {
            BigIntFraction fraction = new BigIntFraction(new BigInteger("1"), new BigInteger("1"));
            for (int i = 2; i <= n; i++) {
                fraction = fraction.add(new BigIntFraction(new BigInteger("1"), new BigInteger(String.valueOf(i))));
            }
            return fraction;
        }
    }
}
