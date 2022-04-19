import numpy as np

def data_to_matrix(path):
    return (
        np.loadtxt(open(path, "rb"), delimiter=",", usecols=[0,1,2,3]),
        np.loadtxt(open(path, "rb"), delimiter=",", usecols=4),
    )

def seidel_method(A, B, eps):
    """ Метод Зейделя """
    print(seidel_method.__doc__)
    D = np.diag(A)
    a = [-(A - np.diagflat(D))[i] / D[i] for i in range(np.shape(A)[0])]
    b = B / D
    X = b.copy() # Початкове наближення
                                                                                                                                                               
    for i in range(10):
        print(f"\tІтерація {i}: {X}")
        X_new = np.zeros_like(X)
        for k in range(A.shape[0]):
            s1 = np.dot(A[k], X_new)
            s2 = np.dot(A[k, k+1:], X[k+1:])
            X_new[k] = (B[k] - s1 - s2) / D[k]
        if np.allclose(X_new, X, atol=eps):
            break
        X = X_new.copy()
    print(f"Відповідь: {X}")

path = input("Введіть шлях до файлу з даними: ") or "data.csv"
A, B = data_to_matrix(path)     # A - матриця коефіцієнтів системи
seidel_method(A, B, 0.001)      # B - матриця вільних членів
