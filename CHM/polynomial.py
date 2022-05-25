import numpy as np
from scipy.linalg import solve

def data_to_matrix(path):
    return (
        np.loadtxt(open(path, "rb"), delimiter=",")[0],
        np.loadtxt(open(path, "rb"), delimiter=",")[1],
    )

def normal_system_of_equations(x, y, m):
    return (
        np.array([[sum([x**(i+j) for x in x]) for i in range(m+1)] for j in range(m+1)]),
        np.array([sum(map(lambda y,x: y * x**i, y, x)) for i in range(m+1)])
    )

def inverse_matrix_method(A, B):
    A_1 = np.array(A)
    for i in range(len(B)):
        for j in range(len(B)):
            tmp = np.delete(A, i, 0)
            tmp = np.delete(tmp, j, 1)
            A_1[i][j] = (-1)**(i+j) * np.linalg.det(tmp) / np.linalg.det(A)
    X = A_1.T @ B
    return [round(x, 4) for x in X]

path = input("Введіть шлях до файлу з даними: ") or "data.csv"
x, y = data_to_matrix(path)

a, b = normal_system_of_equations(x, y, 1)
print(a)
print(b)
print(f"Лінійний: \t {[round(x, 4) for x in solve(a, b)]}")
a, b = normal_system_of_equations(x, y, 2)
print(f"Квадратичний: \t {[round(x, 4) for x in solve(a, b)]}")
a, b = normal_system_of_equations(x, y, 3)
print(f"Кубічний: \t {[round(x, 4) for x in solve(a, b)]}")
