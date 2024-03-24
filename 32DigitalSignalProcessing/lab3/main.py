import numpy as np
import matplotlib.pyplot as plt
from numpy.linalg import lstsq
from numpy.fft import fft, ifft

y = np.array([2.80, 2.94, 3.20, 3.38, 3.53, 3.75])
x = np.linspace(0, 2 * np.pi, len(y), endpoint=False)

A = np.vstack([x**2, x, np.ones(len(x))]).T
coefficients = np.linalg.lstsq(A, y, rcond=None)[0]

poly_approx = A @ coefficients

n = len(y) // 2  # Number of harmonics
c = fft(y) / len(y)  # Fourier coefficients
c[n] = c[n] / 2  # Adjust the middle coefficient if the length is even
fourier_approx = np.real(ifft(c * len(y)))

mae_poly = np.mean(np.abs(y - poly_approx))
mse_poly = np.mean((y - poly_approx)**2)
mae_fourier = np.mean(np.abs(y - fourier_approx))
mse_fourier = np.mean((y - fourier_approx)**2)

plt.figure(figsize=(10, 6))
plt.scatter(x, y, color='red', label='Original Discrete Signal')
plt.plot(x, poly_approx, label='Quadratic Polynomial Approximation', color='blue')
plt.plot(x, fourier_approx, label='Fourier Series Approximation', color='green')
plt.legend()
plt.xlabel('x')
plt.ylabel('Signal Value')
plt.title('Discrete Signal Approximation')
plt.show()

print(f"Quadratic Polynomial Approximation - MAE: {mae_poly:.4f}, MSE: {mse_poly:.4f}")
print(f"Fourier Series Approximation - MAE: {mae_fourier:.4f}, MSE: {mse_fourier:.4f}")

