import numpy as np

def data_to_matrix(path):
    return (
        np.loadtxt(open(path, "rb"), delimiter=",")[0],
        np.loadtxt(open(path, "rb"), delimiter=",")[1],
    )

def lagrange(x, y, x0):
    n = np.shape(x)[0]
    yp = 0
    for i in range(n):
        p = 1
        for j in range(n):
            if i != j:
                p *= (x0 - x[j])/(x[i] - x[j])
        yp += p * y[i]    
    return yp

path = input("Введіть шлях до файлу з даними: ") or "data.csv"
x, y = data_to_matrix(path)
print(f"Результат полінома Лагранжа у точці x0={0.455}: {round(lagrange(x, y, 0.455), 4)}.")
