import numpy as np
import math

# Задана функція
def f(t):
    if -math.pi < t <= 0:
        return t
    elif 0 < t < math.pi:
        return 2 * t

# Завдання 1: Визначення потужності сигналу
def signal_power(f, T):
    # Опрацьовуємо функцію, отримуємо значення
    # потужності сигналу за аналітичним виразом
    # тут вам потрібно використовувати відповідний аналітичний вираз

    # Потужність сигналу
    power_analytical = 0 # Вираз для аналітичного обчислення потужності
    return power_analytical

# Завдання 2: Визначення коефіцієнтів ряду Фур'є
def fourier_coefficients(f, N):
    # Обчислюємо коефіцієнти ряду Фур'є для функції f
    coefficients = []
    for n in range(1, N+1):
        # Обчислюємо коефіцієнт a_n
        an = 0 # Вираз для обчислення коефіцієнта a_n
        # Обчислюємо коефіцієнт b_n
        bn = 0 # Вираз для обчислення коефіцієнта b_n
        coefficients.append((an, bn))
    return coefficients

# Завдання 3: Наближення сигналу рядом Фур'є
def fourier_approximation(coefficients, N, t):
    # Обчислюємо наближення сигналу за рядом Фур'є
    approximation = 0
    for n in range(1, N+1):
        an, bn = coefficients[n-1]
        approximation += an * math.cos(n * t) + bn * math.sin(n * t)
    return approximation

# Завдання 4: Обчислення середньої абсолютної похибки
def mean_absolute_error(f, approximation, T, N):
    # Обчислюємо середню абсолютну похибку
    sum_error = 0
    num_points = 1000 # Кількість точок для обчислення похибки
    for i in range(num_points):
        t = i * T / num_points
        sum_error += abs(f(t) - approximation(t))
    mean_error = sum_error / num_points
    return mean_error

# Завдання 5: Зберігання результатів у файл
def save_to_file(N, coefficients, mean_error):
    # Зберігаємо дані у файл
    with open('results.txt', 'w') as file:
        file.write(f"N: {N}\n")
        file.write("Fourier Coefficients:\n")
        for n, (an, bn) in enumerate(coefficients, 1):
            file.write(f"a_{n}: {an}, b_{n}: {bn}\n")
        file.write(f"Mean Absolute Error: {mean_error}")

# Завдання 6: Основна програма
def main():
    T = 2 * math.pi  # Період сигналу
    N = 10  # Кількість доданків у ряду Фур'є

    # Визначення коефіцієнтів ряду Фур'є
    coefficients = fourier_coefficients(f, N)

    # Обчислення наближеного сигналу рядом Фур'є
    approximation = lambda t: fourier_approximation(coefficients, N, t)

    # Визначення середньої абсолютної похибки
    mean_error = mean_absolute_error(f, approximation, T, N)

    # Зберігання результатів у файл
    save_to_file(N, coefficients, mean_error)

if __name__ == "__main__":
    main()

