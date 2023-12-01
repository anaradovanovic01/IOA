import matplotlib.pyplot as plt

fig = plt.figure()

file = open("file.txt", "r")

x = []
y = []
x_par = []
y_par = []
for line in file:
    arr = line.split(' ')
    a = arr[2].split('\n')
    if arr[2].split('\n')[0] == '1':
        x_par.append(float(arr[0]))
        y_par.append(float(arr[1]))
    else:
        x.append(float(arr[0]))
        y.append(float(arr[1]))
file.close()

plt.scatter(x, y, s=0.1)
plt.scatter(x_par, y_par, s=1)
plt.savefig("grafik.png")
plt.show()

