import numpy as np
import matplotlib.pyplot as plt

y = np.array([2.80, 2.94, 3.20, 3.38, 3.53, 3.75])
x = np.linspace(0, 2 * np.pi, len(y), endpoint=False)
x_fine = np.linspace(0, 2 * np.pi, 1000, endpoint=False)

A = np.vstack([x**2, x, np.ones(len(x))]).T
AtA = A.T @ A
Aty = A.T @ y
coefficients = np.linalg.inv(AtA) @ Aty

poly_approx = A @ coefficients

def fft(y):
    N = len(y)
    n = np.arange(N)
    k = n.reshape((N, 1))
    M = np.exp(-2j * np.pi * k * n / N)
    return np.dot(M, y)

def ifft(c):
    N = c.shape[0]
    n = np.arange(N)
    k = n.reshape((N, 1))
    M = np.exp(2j * np.pi * k * n / N) / N
    return np.dot(M, c)

n = len(y) // 2
c = fft(y) / len(y)
c[n] = c[n] / 2

c_extended = np.concatenate([c[:n+1], np.zeros(len(x_fine) - len(x) - 1), c[-n:]])

fourier_approx_fine = np.real(ifft(c_extended * len(x_fine)))

mae_poly = np.mean(np.abs(y - poly_approx))
mse_poly = np.mean((y - poly_approx)**2)
mae_fourier = np.mean(np.abs(y - np.real(ifft(c * len(y)))))
mse_fourier = np.mean((y - np.real(ifft(c * len(y))))**2)

plt.figure(figsize=(10, 6))
plt.scatter(x, y, color='red', label='Original Discrete Signal')
plt.plot(x, poly_approx, label='Quadratic Polynomial Approximation', color='blue')
plt.plot(x_fine, fourier_approx_fine, label='Fourier Series Approximation', color='green', linewidth=2)
plt.legend()
plt.xlabel('x')
plt.ylabel('Signal Value')
plt.title('Discrete Signal Approximation')
plt.show()

print(f"Quadratic Polynomial Approximation - MAE: {mae_poly:.4f}, MSE: {mse_poly:.4f}")
print(f"Fourier Series Approximation - MAE: {mae_fourier:.4f}, MSE: {mse_fourier:.4f}")

