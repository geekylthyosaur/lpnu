import numpy as np
import matplotlib.pyplot as plt

# Ваш дискретний сигнал
y = np.array([4.44, 5.43, 6.01, 7.35, 8.07, 9.89])
n = len(y)  # Кількість значень сигналу
x = np.linspace(-np.pi, np.pi, n)  # x_i розподілені рівномірно на [-π, π]

# Апроксимація поліномом другого степеня за методом найменших квадратів
X = np.vstack([x**0, x, x**2]).T  # Матриця дизайну
coeff_poly = np.linalg.inv(X.T @ X) @ X.T @ y  # Коефіцієнти полінома

# Функція для апроксимації поліномом
def poly_approx(x):
    return coeff_poly[0] + coeff_poly[1]*x + coeff_poly[2]*x**2

# Наближення рядом Фур’є
a_0 = 2/n * np.sum(y)
a_k = lambda k: 2/n * np.sum(y * np.cos(k*x))
b_k = lambda k: 2/n * np.sum(y * np.sin(k*x))

# Функція для наближення рядом Фур’є
def fourier_series(x, n_terms=3):
    approximation = a_0 / 2
    for k in range(1, n_terms + 1):
        approximation += a_k(k) * np.cos(k*x) + b_k(k) * np.sin(k*x)
    return approximation

# Масив точок для наближення
x_dense = np.linspace(-np.pi, np.pi, 1000)

# Виконуємо апроксимацію та наближення
y_poly = poly_approx(x_dense)
y_fourier = fourier_series(x_dense, n_terms=3)

# Порівняння апроксимації та наближення з оригінальним сигналом
plt.figure(figsize=(10, 6))
plt.scatter(x, y, label='Original Signal', color='black')
plt.plot(x_dense, y_poly, label='2nd Degree Polynomial Approximation', linestyle='--', color='blue')
plt.plot(x_dense, y_fourier, label='Fourier Series Approximation', linestyle='-', color='red')
plt.legend()
plt.xlabel('x')
plt.ylabel('y')
plt.title('Approximation and Fourier Series Fitting')
plt.show()

# Обчислення середніх абсолютних похибок
mae_poly = np.mean(np.abs(y - poly_approx(x)))
mae_fourier = np.mean(np.abs(y - fourier_series(x, n_terms=3)))

print(f"Коефіцієнти квадратичного полінома: {coeff_poly}")
print(f"Середня абсолютна похибка для полінома: {mae_poly:.4f}")
print(f"Середня абсолютна похибка для ряду Фур’є: {mae_fourier:.4f}")

