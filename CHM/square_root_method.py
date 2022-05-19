from numpy import transpose, linalg, loadtxt

def data_to_matrix(path):
    return (
        loadtxt(open(path, "rb"), delimiter=",", usecols=[0,1,2]),
        loadtxt(open(path, "rb"), delimiter=",", usecols=3),
    )

def square_root_method(A, B):
    """ Метод квадратного кореня """
    print(square_root_method.__doc__)
    L = linalg.cholesky(A)
    L_T = transpose(L)
    Y = linalg.inv(L) @ B
    print(f" L: \n {L} \n Y: \n {Y}")
    print(L_T)
    X = linalg.inv(L_T) @ Y
       
    print("Відповідь:", [round(x, 4) for x in X])

path = input("Введіть шлях до файлу з даними: ") or "data.csv"
A, B = data_to_matrix(path)

N = transpose(A) @ A
C = transpose(A) @ B

print(f" N: \n {N} \n C: \n {C}")

square_root_method(N, C)
