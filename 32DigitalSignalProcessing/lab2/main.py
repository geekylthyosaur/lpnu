import numpy as np
import matplotlib.pyplot as plt

y = np.array([4.44, 5.43, 6.01, 7.35, 8.07, 9.89])
n = len(y)
x = np.linspace(-np.pi, np.pi, n)
x_smooth = np.linspace(-np.pi, np.pi, 300)

def polynomial_approximation(x, y):
    coeffs = np.polyfit(x, y, 2)
    y_poly = np.polyval(coeffs, x)
    mae_poly = np.mean(np.abs(y - y_poly))
    rmse_poly = np.sqrt(np.mean((y - y_poly)**2))
    return y_poly, mae_poly, rmse_poly, coeffs

def fourier_series(x, y, smooth_x):
    a_0 = np.sum(y) * 2 / n
    a_k = lambda k: np.sum(y * np.cos(k * x)) * 2 / n
    b_k = lambda k: np.sum(y * np.sin(k * x)) * 2 / n
    
    return lambda smooth_x: a_0 / 2 + sum(a_k(k) * np.cos(k * smooth_x) + b_k(k) * np.sin(k * smooth_x) for k in range(1, 5))

y_poly, mae_poly, rmse_poly, coeffs_poly = polynomial_approximation(x, y)
fourier_func = fourier_series(x, y, x_smooth)
y_fourier_smooth = fourier_func(x_smooth)
mae_fourier = np.mean(np.abs(y - fourier_func(x)))
rmse_fourier = np.sqrt(np.mean((y - fourier_func(x))**2))

plt.figure(figsize=(10, 6))
plt.plot(x, y, 'o', label='Original Signal')
plt.plot(x, y_poly, '-', label='Quadratic Polynomial Approximation')
plt.plot(x_smooth, y_fourier_smooth, '-', label='Fourier Series Approximation', linewidth=2)
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

