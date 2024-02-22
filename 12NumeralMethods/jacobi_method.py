import numpy as np

def data_to_matrix(path):
    return (
        np.loadtxt(open(path, "rb"), delimiter=",", usecols=[0,1,2,3]),
        np.loadtxt(open(path, "rb"), delimiter=",", usecols=4),
    )

def jacobi_method(A, B, eps):
    """ Метод Якобі """
    print(jacobi_method.__doc__)
    D = np.diag(A)
    a = np.array([-(A - np.diagflat(D))[i] / D[i] for i in range(np.shape(A)[0])])    # alpha
    b = B / D                                                               # beta 

    print(f"α:\n{a}\nβ:\n{b}")

    X = b.copy() # Початкове наближення

    for i in range(10):
        print(f"\tІтерація {i}: {X}")
        X_new = b + np.dot(a, X)
        if np.allclose(X_new, X, atol=eps):
            break
        X = X_new.copy()
    print(f"Відповідь: {X}")

path = input("Введіть шлях до файлу з даними: ") or "data.csv"
A, B = data_to_matrix(path)     # A - матриця коефіцієнтів системи
jacobi_method(A, B, 0.001)      # B - матриця вільних членів
