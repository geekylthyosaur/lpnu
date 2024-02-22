import numpy as np

def data_to_matrix(path):
    return (
        np.loadtxt(open(path, "rb"), delimiter=",", usecols=[0,1,2]),
        np.loadtxt(open(path, "rb"), delimiter=",", usecols=3),
    )

def inverse_matrix_method(A, B, n):
    """ Метод оберненої матриці """
    print(inverse_matrix_method.__doc__)
    A_1 = np.array(A) # Обернена матриця коефіцієнтів
    for i in range(n):
        for j in range(n):
            tmp = np.delete(A, i, 0)
            tmp = np.delete(tmp, j, 1)
            A_1[i][j] = (-1)**((i) + (j)) * np.linalg.det(tmp) / np.linalg.det(A)
    A_1 = np.transpose(A_1)
    print(f"Обернена матриця: \n{A_1}")
    X = np.matmul(A_1, B) # Множення оберненої матриці коефіцієнтів на матрицю констант
    print("Відповідь: ", [round(x, 4) for x in X])

path = input("Введіть шлях до файлу з даними: ") or "data.csv"
A, B = data_to_matrix(path)
inverse_matrix_method(A, B, np.shape(A)[0])
