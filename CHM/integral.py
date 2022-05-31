import numpy as np
from scipy.misc import derivative
import math

def title(a, b, n):
    h = (b-a)/n
    xi = [x for x in np.arange(a, b+h, h)]
    yi = [f(x) for x in xi]
    print("Xi:\t", end="")
    [print(f"{x:8.4f}", end="") for x in xi]
    print("\nYi:\t", end="")
    [print(f"{y:8.4f}", end="") for y in yi]
    print("")

def echo(name, xi, si, res, R):
    print(f"{name}: ")
    print("\tSi:\t", end="")
    [print(f"{s:8.4f}", end="") for s in si]
    print(f"\n\tВ-дь: \t {round(res, 4)} +-{round(R, 4)}")

def f(x):
    return math.log(1+abs(x))**2

def d2f(x):
    return derivative(f, 2)

def d4f(x):
    return derivative(f, 4)

def rect(a, b, n):
    h = (b - a)/n
    def left_rect():
        """Ліві прямокутники"""
        xi = [x for x in np.arange(a, b, h)]
        si = [h * f(x) for x in xi]
        res = sum(si)
        r = R(a, b, h)
        echo(left_rect.__doc__, xi, si, res, r)

    def right_rect():
        """Праві прямокутники"""
        xi = [x for x in np.arange(a+h, b+h, h)]
        si = [h * f(x) for x in xi]
        res = sum(si)
        r = R(a+h, b+h, h)
        echo(right_rect.__doc__, xi, si, res, r)

    def central_rect():
        """Середні прямокутники"""
        xi = [x for x in np.arange(a+(h/2), b+(h/2), h)]
        si = [h * f(x) for x in xi]
        res = sum(si)
        r = R(a+(h/2), b+(h/2), h)
        echo(central_rect.__doc__, xi, si, res, r)

    def R(a, b, h):
        return max([(d2f(x)/24)*(b-a)*h**2 for x in np.arange(a, b, h)])
    left_rect()
    right_rect()
    central_rect()

def trapeze(a, b, n):
    """Трапеції"""
    h = (b - a)/n
    xi = np.arange(a, b+h, h)
    si = [h * ((f(xi[i-1]) + f(xi[i]))/2) for i in range(1, n+1)]
    res = sum(si)
    r = max([(d2f(x)/12)*(b-a)*h**2 for x in xi])
    echo(trapeze.__doc__, xi, si, res, r)

def simpson(a, b, n):
    """Сімпсон"""
    h = (b - a)/n
    xi = np.arange(a, b+h, h)
    si = [(h/3) * (f(xi[i]) + 4*f(xi[i+1]) + f(xi[i+2])) for i in range(0, n, 2)]
    res = sum(si)  
    r = max([((b-a)**5*d4f(x))/(180*n**4) for x in xi])
    echo(simpson.__doc__, xi, si, res, r)

a, b = [int(x) for x in input("Введіть межі інтегрування: ").split()]
n = int(input("Введіть кількість ітерацій: "))
title(a, b, n)
rect(a, b, n)
trapeze(a, b, n)
simpson(a, b, n)
