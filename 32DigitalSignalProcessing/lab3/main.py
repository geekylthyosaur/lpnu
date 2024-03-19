import numpy as np
import matplotlib.pyplot as plt
from numpy.fft import fft, ifft

y = np.array([2.80, 2.94, 3.20, 3.38, 3.53, 3.75])
x = np.linspace(0, 2 * np.pi, len(y), endpoint=False)

A = np.vstack([x**2, x, np.ones(len(x))]).T
coeffs = np.linalg.lstsq(A, y, rcond=None)[0]
quad_approx = np.polyval(coeffs[::-1], x)

y_fft = fft(y)
N = len(y)
y_fft_approx = ifft(y_fft[:3], N)

plt.figure(figsize=(10, 6))
plt.plot(x, y, 'o', label='Original Signal')
plt.plot(x, quad_approx, label='Quadratic Polynomial Approximation')
plt.plot(x, y_fft_approx, label='Fourier Series Approximation')
plt.legend()
plt.show()

quad_error = np.mean(np.abs(y - quad_approx))
fourier_error = np.mean(np.abs(y - y_fft_approx))

print(f"Quadratic Polynomial Approximation Error: {quad_error}")
print(f"Fourier Series Approximation Error: {fourier_error}")

