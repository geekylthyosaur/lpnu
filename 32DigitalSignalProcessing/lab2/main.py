import numpy as np
import matplotlib.pyplot as plt

y = np.array([4.44, 5.43, 6.01, 7.35, 8.07, 9.89])
n = len(y)
x = np.linspace(-np.pi, np.pi, n)

def polynomial_approximation(x, y):
    coeffs = np.polyfit(x, y, 2)  # Коефіцієнти апроксимаційного поліному
    y_poly = np.polyval(coeffs, x)
    mae_poly = np.mean(np.abs(y - y_poly))
    rmse_poly = np.sqrt(np.mean((y - y_poly)**2))
    return y_poly, mae_poly, rmse_poly, coeffs

def fourier_series(x, y):
    a_0 = np.sum(y) * 2 / n
    a_k = lambda k: np.sum(y * np.cos(k * x)) * 2 / n
    b_k = lambda k: np.sum(y * np.sin(k * x)) * 2 / n
    
    return lambda x: a_0 / 2 + sum(a_k(k) * np.cos(k * x) + b_k(k) * np.sin(k * x) for k in range(1, 5))

y_poly, mae_poly, rmse_poly, coeffs_poly = polynomial_approximation(x, y)
fourier_func = fourier_series(x, y)
y_fourier = fourier_func(x)
mae_fourier = np.mean(np.abs(y - y_fourier))
rmse_fourier = np.sqrt(np.mean((y - y_fourier)**2))

plt.figure(figsize=(10, 6))
plt.plot(x, y, 'o', label='Original Signal')
plt.plot(x, y_poly, '-', label='Quadratic Polynomial Approximation')
plt.plot(x, y_fourier, '--', label='Fourier Series Approximation', linewidth=2)
plt.legend()
plt.xlabel('x')
plt.ylabel('y')
plt.title('Signal Approximation')
plt.show()

print(f"MAE for Quadratic Polynomial: {mae_poly}")
print(f"RMSE for Quadratic Polynomial: {rmse_poly}")
print(f"MAE for Fourier Series: {mae_fourier}")
print(f"RMSE for Fourier Series: {rmse_fourier}")
print(f"Коефіцієнти апроксимаційного поліному: {coeffs_poly}")

