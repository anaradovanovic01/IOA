import matplotlib.pyplot as plt
import numpy as np
import math


def fs(x):
    n = 5
    beta = 20 * np.pi
    teta = np.pi / 4
    d = 1 / 20
    Fs = 0
    fi = x + beta * d * math.cos(teta)
    for k in range(0, n):
        Fs += math.e ** complex(0, k * fi)
    return abs(Fs)


def fs_niz(points):
    arr = []
    for i in points:
        arr.append(abs(fs(i)))
    return arr


def izvod(x):
    deltax = 10 ** (-7)
    return (fs(x + deltax) - fs(x)) / deltax

#crtanje grafika
fig = plt.figure()
x = np.arange(0, 2 * np.pi, 0.05)

plt.plot(x, fs_niz(x))
y = []
for i in x:
    y.append(izvod(i))
d = izvod(0.1)
plt.plot(x, y)
plt.savefig("grafik.png")
plt.show()

#pronalazenje maksimuma funkcije
a = 3.5
b = 4.5
c = 0.5 * (a + b)

while abs(a - b) > 10 ** (-7):
    if izvod(a) * izvod(c) < 0:
        b = c
    else:
        a = c
    c = 0.5 * (a + b)

print("x =", c)
print("y =", fs(c))
