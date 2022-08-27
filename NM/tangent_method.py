class TangentMethod:
    def __init__(self, a, b, eps, f, first_der, second_der):
        self.a = a # Ліва межа
        self.b = b # Права межа
        self.x = 1 # Шукане значення
        self.i = 0 # Кількість ітерацій
        self.eps = eps # Точність
        self.f = f # Функція
        self.first_der = first_der # Перша похідна функції
        self.second_der = second_der # Друга похідна функції

        if a >= b:
            return print("Помилка, 'a' більше або рівне 'b'")
        elif eps > b - a:
            return print("Помилка, 'eps' більше ніж інтервал між 'a' та 'b'")
        elif self.calc_f(f, a) * self.calc_f(self.second_der, a) > 0:
            x = a
        else:
            x = b


    def calculate(self):
        print(f"x: {self.x} f(x): {self.calc_f(self.f, self.x)} f'(x): {self.calc_f(self.first_der, self.x)}")
        if abs(self.calc_f(self.f, self.x)) < self.eps:
            return f"Відповідь: {self.x} \nКількість ітерацій: {self.i}"
        else:
            self.i += 1
            self.x -= self.calc_f(self.f, self.x) / self.calc_f(self.first_der, self.x)
            return self.calculate()


    def calc_f(self, f, x):
        return eval(f.replace("x", str(x)))

a = float(input("Ліва межа: "))
b = float(input("Права межа: "))
eps = float(input("Точність: "))
f = input("Функція: x**3-6*x**2-7") or "x*x*x - 6*x*x - 7"
first_der = input("Перша похідна функції: 3**2-12*x ") or "3*x*x - 12*x"
second_der = input("Друга похідна функції: 6*x-12") or "6*x - 12"

print(TangentMethod(a, b, eps, f, first_der, second_der).calculate())

