public interface Fraction<T> {
    T add(T other);
    void reduce();
    String toString();
}