import numpy as np

def gauss_method(A, n):
    """ Метод Гауса """
    print(gauss_method.__doc__)
    for i in range(n):
        print(A)
        if A[i][i] == 0.0: 
            exit("Помилка: елемент головної діагоналі = 0")
        for j in range(n):
            if i != j:
                ratio = A[j][i]/A[i][i]
                for k in range(n + 1):
                    A[j][k] -= ratio * A[i][k]
    print(A)
    print("Відповідь: ", [round(A[i][n]/A[i][i], 4) for i in range(n)])

path = input("Введіть шлях до файлу з даними: ") or "data.csv"
A = np.loadtxt(open(path, "rb"), delimiter=",")
gauss_method(A, np.shape(A)[0])
