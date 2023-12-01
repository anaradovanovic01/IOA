import random
import numpy as num
import matplotlib.pyplot as plot

D = 64
s = [173669, 275487, 1197613, 1549805, 502334, 217684, 1796841, 274708, 631252, 148665, 150254, 4784408, 344759, 440109, 4198037, 329673, 28602, 144173, 1461469, 187895, 369313, 959307, 1482335, 2772513, 1313997, 254845, 486167, 2667146, 264004, 297223, 94694, 1757457, 576203, 8577828, 498382, 8478177, 123575, 4062389, 3001419, 196884, 617991, 421056, 3017627, 131936, 1152730, 2676649, 656678, 4519834, 201919, 56080, 2142553, 326263, 8172117, 2304253, 4761871, 205387, 6148422, 414559, 2893305, 2158562, 465972, 304078, 1841018, 1915571]
size = 2**25
T0 = 64*1024*1024
maxIter = 100000
reannealing = 20
hammingMinimum = 1
hammingMaximum = 5
step = 0.95

array = []

def makeArray():
    tmpArray = []
    for i in range(0,64):
        number = random.randint(0,2)
        tmpArray.append(number)
    return tmpArray

def newArray(sel, hamming):
    newArr = [];
    for i in range(len(sel)):
        newArr.append(sel[i]);
    for i in range(hamming):
        ind = random.randint(0, 63)
        num = random.randint(0,2)
        newArr[ind] = num
    return newArr;

def hammingDistance(current):
    return round((hammingMinimum - hammingMaximum)/(maxIter - 1)) * (current - 1) + hammingMaximum

def function(x):
    F1 = 0
    F2 = 0
    for i in range(len(x)):
        if(x[i] == 1):
            F1 += s[i]
        elif(x[i] == 2):
            F2 += s[i]
    function1 = size - F1;
    function2 = size - F2;
    if(function1 >= 0 and function2 >= 0):
        return function1 + function2
    else:
        return 2**26

def annealing(array):
    finalArray = []
    opt = function(array)
    # print('izracunao opt fun')
    bestResult = array
    for i in range(0, 10):
        currentResult = opt
        currentArray = bestResult
        temperature = T0
        # print('zapocinjem iteraciju', i)
        for j in range(0, maxIter):
            hamming = hammingDistance(j)
            #print('hamming', hamming)
            tmp = newArray(currentArray, hamming)
            #print('kreirao tmp', tmp)
            tmpResult = function(tmp)
            #print('izracunao tmp result', tmpResult)

            delta = tmpResult - currentResult
            #print('delta', delta)
            if delta < 0:
                currentResult = tmpResult
                currentArray = tmp
                if opt > tmpResult:
                    opt = tmpResult
                    bestResult = tmp
            elif num.exp(-delta/temperature) > random.uniform(0, 1):
                currentResult = tmpResult
                currentArray = tmp
            finalArray.append(opt)
            temperature = step * temperature
    print('Niz: ')
    print(bestResult)
    print('Resenje: ')
    print(min(finalArray))
    return finalArray




yAverageBest = []
for i in range(1000000):
    yAverageBest.append(0)

xOsa = num.arange(0, 1000000, 1)
yOsa = []

for i in range(0, reannealing):
    print('Iter', i)
    x = makeArray()
    final = annealing(x)

    for j in range(0, len(final)):
        yAverageBest[j] = yAverageBest[j] + final[j]
    yOsa.append(final)

    plot.plot(xOsa, yOsa[i])


plot.yscale("log")
plot.xscale("log")
plot.show()
plot.figure()

for j in range(0, len(yAverageBest)):
    yAverageBest[j] = yAverageBest[j] / 20

plot.plot(xOsa, yAverageBest)
plot.yscale("log")
plot.xscale("log")
plot.show()





