import random
import matplotlib.pyplot as plt
import numpy as np
import math
import scipy as scipy


def y_training(x):
    return -1 + 2 * (math.pow(math.sin(math.pi/2*(x+1)), 4) + 1/4*math.pow(math.sin(math.pi/2*math.pow((1-abs(math.cos(math.pi/4*(x+1)))), 4)), 4))


def y_out(x, w):
    s = 0
    for i in range(0, 5):
        s += w[i+10] * np.tanh(w[i]*x + w[i+5])
    return w[15] + s


def f(w):
    s = 0
    for x in x_in:
        s += math.pow((y_out(x, w) - y_training(x)), 2)
    return s / 101


fig = plt.figure()
x_in = np.arange(-1, 1, 0.02)

yt = []
for x in x_in:
    yt.append(y_training(x))
plt.plot(x_in, yt)

w = []
for i in range(0, 16):
    w.append(random.uniform(-5.0, 5.0))

b = [[-5, 5], [-5, 5], [-5, 5], [-5, 5], [-5, 5], [-5, 5], [-5, 5], [-5, 5], [-5, 5], [-5, 5], [-5, 5], [-5, 5], [-5, 5], [-5, 5], [-5, 5], [-5, 5]]

while f(w) > 10**(-4):
    results = scipy.optimize.minimize(f, w, method='Nelder-Mead', bounds=b)
    w = results.x

print(results.fun)

for i in range(0, 16):
    print("w", i+1, "= ", "{:.15f}".format(w[i]), sep='')

yo = []
for x in x_in:
    yo.append(y_out(x, w))
plt.plot(x_in, yo)

plt.savefig("grafik.png")
plt.grid()
plt.show()

