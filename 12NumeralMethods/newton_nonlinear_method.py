from numpy import array, linalg
from numpy.linalg import norm, inv as invert
from math import sin, cos

def newton_method(X, f, j, eps):
    """Метод Ньютона"""
    print(newton_method.__doc__)
    for i in range(1, int(1e6)):
        deltaX = invert(j(X)) @ f(X)
        X -= deltaX 
        print(f"i:{i}  X:[{round(X[0], 3)}, {round(X[1], 3)}]")
        if norm(deltaX) < eps:
            break
    return X

def f(args):
    x, y = args
    return array((1.5 - sin(x+2) + y, 0.5 - cos(y-2) - x))

def j(args):
    x, y = args
    return array((
        (-cos(x+2), 1),
        (-1, -sin(2-y)),
    ))

newton_method([1,-1], f, j, 10e-3)
