from math import sin, cos

def phi(x, y):
    phi1 = 0.5 - cos(y-2)
    phi2 = sin(x+2) - 1.5
    return (phi1, phi2)

eps = 0.001
i = 0

def iteration_method(x, y):
    """Метод простих ітерацій"""
    (x_new, y_new) = phi(x, y)
    global i
    i += 1
    print(f"i:{i}  X:[{round(x_new, 3)}, {round(y_new, 3)}]")
    if abs(x_new - x) + abs(y_new - y) < eps: 
        return
    else:
        return iteration_method(x_new, y_new)

print(iteration_method.__doc__)
iteration_method(1, -1)
