import numpy as np
import matplotlib.pyplot as plt

# y = np.array([4.44, 5.43, 6.01, 7.35, 8.07, 9.89])
y = np.array([3.01, 2.78, 2.52, 2.42, 2.19, 1.95])
n = len(y)
x = np.linspace(-np.pi, np.pi, n)
dx = x[1] - x[0]

def fourier_series_rect_rule(x, y, n_terms):
    a_0 = np.sum(y) * dx / np.pi
    a_k = lambda k: np.sum(y * np.cos(k * x)) * dx / (np.pi*k)
    b_k = lambda k: np.sum(y * np.sin(k * x)) * dx / (np.pi*k)
    
    return lambda x: a_0 / 2 + sum(a_k(k) * np.cos(k * x) + b_k(k) * np.sin(k * x) for k in range(1, n_terms + 1))

n_terms = 10
fourier_func = fourier_series_rect_rule(x, y, n_terms)
y_fourier = fourier_func(x)

plt.figure(figsize=(10, 6))
plt.plot(x, y, 'o', label='Original Signal')
plt.plot(x, np.polyval(np.polyfit(x, y, 2), x), '-', label='Quadratic Polynomial Approximation')
plt.plot(x, y_fourier, '--', label='Fourier Series Approximation', linewidth=2)
plt.legend()
plt.xlabel('x')
plt.ylabel('y')
plt.title('Signal Approximation')
plt.show()

# Calculating and printing the MAE for both methods
mae_poly = np.mean(np.abs(y - np.polyval(np.polyfit(x, y, 2), x)))
mae_fourier = np.mean(np.abs(y - y_fourier))
print(f"MAE for Quadratic Polynomial: {mae_poly}")
print(f"MAE for Fourier Series: {mae_fourier}")

