class IterationMethod:
    def __init__(self, a, b, eps, f, phi):
        self.a = a # Ліва межа
        self.b = b # Права межа
        self.x = 6.5 # Шукане значеня
        self.i = 0 # Кількість ітерацій
        self.eps = eps # Точність
        self.f = f # Функція
        self.phi = phi # Канонічні форма функції

        if a >= b:
            print("Помилка, 'a' більше або рівне 'b'")
            exit(1)
        elif eps > b - a:
            print("Помилка, 'eps' більше ніж інтервал між 'a' та 'b'")
            exit(1)


    def calculate(self):
        print(f"x: {self.x} f(x): {self.calc_f(self.f, self.x)}")
        if abs(self.calc_f(self.f, self.x)) < self.eps:
            return f"Відповідь: {self.x} \nКількість ітерацій: {self.i}"
        else:
            self.i += 1
            self.x = self.calc_f(self.phi, self.x)
            return self.calculate()


    def calc_f(self, f, x):
        return eval(f.replace("x", str(x)))

a = float(input("Ліва межа: "))
b = float(input("Права межа: "))
eps = float(input("Точність: "))
f = input("Функція: x**3-6*x**2-7") or "x*x*x - 6*x*x - 7"
phi = input("Функція у канонічній формі: (6*x*x + 7)**(1/3)") or "(6*x*x + 7)**(1/3)"

print(IterationMethod(a, b, eps, f, phi).calculate())

