import numpy as np

def data_to_matrix(path):
    return (
        np.loadtxt(open(path, "rb"), delimiter=",")[0],
        np.loadtxt(open(path, "rb"), delimiter=",")[1],
    )

def newton(x, y, r):
    n = len(x)
    a = [y[i] for i in range(n)]
    for j in range(1, n):
        for i in range(n-1, j-1, -1):
            a[i] = (a[i] - a[i-1]) / (x[i] - x[i-j])

    n = len(a) - 1
    temp = a[n] + (r - x[n])
    for i in range(n - 1, -1, -1):
        temp = temp * (r - x[i]) + a[i]
    return temp

path = input("Введіть шлях до файлу з даними: ") or "data.csv"
x, y = data_to_matrix(path)
print(f"Результат полінома Ньютона у точці x0=0.455: {round(newton(x, y, 0.455), 4)}.")
