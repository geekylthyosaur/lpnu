import numpy as np
from scipy.misc import derivative
import math

def f(x):
    return math.log(1+abs(x))**2

def d2f(x):
    return derivative(f, 2)

def d4f(x):
    return derivative(f, 4)

def rect(a, b, n):
    h = (b - a)/n
    def left_rect():
        print(f"Ліві прямокутники: \t {round(h * sum([f(x) for x in np.arange(a, b, h)]), 6)}", end=" ")
        R(a, b, h)

    def right_rect():
        print(f"Праві прямокутники: \t {round(h * sum([f(x) for x in np.arange(a+h, b+h, h)]), 6)}", end=" ")
        R(a+h, b+h, h)

    def central_rect():
        print(f"Середні прямокутники: \t {round(h * sum([f(x) for x in np.arange(a+(h/2), b+(h/2), h)]), 6)}", end=" ")
        R(a+(h/2), b+(h/2), h)
    
    def R(a, b, h):
            print(f"+-{round(max([(d2f(x)/24)*(b-a)*h**2 for x in np.arange(a, b, h)]), 6)}")
    left_rect()
    right_rect()
    central_rect()

def trapeze(a, b, n):
    h = (b - a)/n
    x = np.arange(a, b+h, h)
    print(f"Трапеції: \t\t {round(h * sum([(f(x[i]) + f(x[i+1]))/2 for i in range(n)]), 6)}", end=" ")
    def R():
        print(f"+-{round(max([-(d2f(x)/12)*(b-a)*h**2 for x in np.arange(a, b, h)]), 6)}")
    R()

def simpson(a, b, n):
    h = (b - a)/n
    x = np.arange(a, b+h, h)
    print(f"Сімпсон: \t\t {round((h/3) * sum([f(x[0]), f(x[n]), 2*sum([f(x[i]) for i in range(2, n-1, 2)]), 4*sum([f(x[i]) for i in range(1, n, 2)])]), 6)}", end=" ")  
    def R():
        print(f"+-{round(max([((b-a)**5*d4f(x))/(180*n**4) for x in np.arange(a, b, h)]), 8)}")
    R()

a, b = [int(x) for x in input("Введіть межі інтегрування: ").split()]
rect(a, b, 100)
trapeze(a, b, 100)
simpson(a, b, 100)
