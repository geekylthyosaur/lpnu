import numpy as np

def data_to_matrix(path):
    return (
        np.loadtxt(open(path, "rb"), delimiter=",", usecols=[0,1,2]),
        np.loadtxt(open(path, "rb"), delimiter=",", usecols=3),
    )

def invert_matrix(A, n):
    A_1 = np.array(A)
    for i in range(n):
        for j in range(n):
            tmp = np.delete(A, i, 0)
            tmp = np.delete(tmp, j, 1)
            A_1[i][j] = (-1)**((i) + (j)) * np.linalg.det(tmp) / np.linalg.det(A)
    return np.transpose(A_1)

def lu_decomposition_method(A, B, n):
    """ Метод LU-розкладу """
    print(lu_decomposition_method.__doc__)
    L = np.zeros(np.shape(A))
    U = np.zeros(np.shape(A))
    for j in range(n): # Метод Краута
        U[j][j] = 1
        for i in range(j, n):
            alpha = A[i][j]
            for k in range(j):
                alpha -= L[i][k]*U[k][j]
            L[i][j] = alpha
        for i in range(j+1, n):
            tempU = A[j][i]
            for k in range(j):
                tempU -= L[j][k]*U[k][i]
            U[j][i] = tempU/L[j][j]
    Y = np.matmul(invert_matrix(L, n), B) # Обчислюємо Y
    X = np.matmul(invert_matrix(U, n), Y) # Обчислюємо X
    print(f"L: \n{L}")
    print(f"U: \n{U}")
    print(f"Y: \n{Y}")
    print("Відповідь:", [round(x, 4) for x in X])

path = input("Введіть шлях до файлу з даними: ") or "data.csv"
A, B = data_to_matrix(path)
lu_decomposition_method(A, B, np.shape(A)[0])
