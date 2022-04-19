import numpy as np

def data_to_matrix(path):
    return (
        np.loadtxt(open(path, "rb"), delimiter=",", usecols=[0,1,2]),
        np.loadtxt(open(path, "rb"), delimiter=",", usecols=3),
    )

def cramer_method(A, B):
    """ Метод Крамера """
    print(cramer_method.__doc__)
    d = np.linalg.det(A) # Детермінант початкової матриці коефіцієнтів
    m1 = np.array([B, A[:,1], A[:,2]])
    m2 = np.array([A[:,0], B, A[:,2]]) # Підстановка константних
    m3 = np.array([A[:,0], A[:,1], B]) # значень в матриці коефіцієнтів
    d1 = np.linalg.det(m1)
    d2 = np.linalg.det(m2) # Детермінант змінених матриць
    d3 = np.linalg.det(m3)
    print(f"d: {d:.{4}f}; d1: {d1:.{4}f}; d2: {d2:.{4}f}; d3: {d3:.{4}f}")
    x1 = d1 / d
    x2 = d2 / d # Результат
    x3 = d3 / d
    print("Відповідь: ", [round(x, 4) for x in [x1, x2, x3]])

path = input("Введіть шлях до файлу з даними: ") or "data.csv"
A, B = data_to_matrix(path)
cramer_method(A, B)
