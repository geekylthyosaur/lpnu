class DichotomyMethod:
    """ Метод Дихотомії """

    def __init__(self, a, b, eps, f):
        self.a = a # Ліва межа
        self.b = b # Права межа
        self.x = 0 # Шуканий корінь
        self.eps = eps # Точність
        self.f = f # Функція

    def calculate(self):
        self.x = (self.a + self.b)/2
        print(f"a: {self.a}; b: {self.b}; x: {self.x}; f(x): {self.calc_func(self.x, self.f)}")
        if abs(self.calc_func(self.x, self.f)) < self.eps: return
        elif self.a == self.b: return print("No roots")
        elif self.calc_func(self.a, self.f) * self.calc_func(self.x, self.f) < 0:
            self.b = self.x
            return self.calculate()
        else:
            self.a = self.x
            return self.calculate()

    def calc_func(self, x, f):
        return eval(f.replace("x", str(x)))

a = float(input("Введіть ліву межу: "))
b = float(input("Введіть праву межу: "))
eps = float(input("Введіть точність: "))
f = input("Введіть функцію: ")

d = DichotomyMethod(a, b, eps, f)
d.calculate()

