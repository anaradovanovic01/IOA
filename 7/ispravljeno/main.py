import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
x = np.arange(0, 1000000, 10)

file = open("file.txt", "r")

y = []
for line in file:
    t = []
    arr = line.split(' ')
    for i in range(len(arr)-1):
        t.append(int(arr[i]))
    y.append(t)
file.close()

for i in range(20):
    plt.loglog(x, y[i])
plt.savefig("grafik.png")
plt.show()

fig = plt.figure()
c =[]
for i in range(100000):
    sum = 0
    for j in range(20):
        sum += y[j][i]
    c.append(1/20 * sum)
plt.loglog(x, c)
plt.savefig("grafik2.png")
plt.show()
