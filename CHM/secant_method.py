class SecantMethod:
    """ Метод Хорд """

    def __init__(self, a, b, eps, f, f2):
        self.a = a # Ліва межа
        self.b = b # Права межа
        self.x = 0 # Шуканий корінь
        self.c = 0 # Нерухомий кінець
        self.eps = eps # Точність
        self.f = f # Функція
        self.f2 = f2 # Друга похідна функції

        if self.calc_func(self.a, self.f) * self.calc_func(self.a, self.f2) > 0:
            self.x = self.b
            self.c = self.a
        else:
            self.x = self.a
            self.c = self.b


    def calculate(self):
        print(f"a: {self.a};b: {self.b};c: {self.c}; x: {self.x}; f(x): {self.calc_func(self.x, self.f)}")
        if abs(self.calc_func(self.x, self.f)) < self.eps: return 
        self.x = self.x - (self.calc_func(self.x, self.f) * (self.c - self.x)) / (self.calc_func(self.c, self.f) - self.calc_func(self.x, self.f))
        return self.calculate()

    def calc_func(self, x, f):
        return eval(f.replace("x", str(x)))


a = float(input("Введіть ліву межу: "))
b = float(input("Введіть праву межу: "))
eps = float(input("Введіть точність: "))
f = input("Введіть функцію: ")
f2 = input("Введіть другу похідну функції: ")

s = SecantMethod(a, b, eps, f, f2)
s.calculate()

