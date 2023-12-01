#include <math.h>
#include <random>
#include <iostream>
#include <fstream>
using namespace std;

int fun(int s[], int x[], int n) {
    int f1, f2, f;
    f1 = pow(2, 25);
    f2 = pow(2, 25);
    for (int i = 0; i < n; i++) {
        if (x[i] == 1)
            f1 -= s[i];
        if (x[i] == 2)
            f2 -= s[i];
    }
    if (f1 < 0 || f2 < 0)
        f = pow(2, 26);
    else
        f = f1 + f2;
    return f;
}

int main() {
    const int numOfIterations = 100000;
    const int reannealingNum = 10;
    const int numOfFiles = 64;
    const int numOfRuns = 20;
    
    int s[] = { 173669, 275487, 1197613, 1549805, 502334, 217684, 1796841, 274708, 631252, 148665, 150254, 4784408, 344759, 440109, 4198037, 329673, 28602, 144173, 1461469, 187895, 369313, 959307, 1482335, 2772513, 1313997, 254845, 486167, 2667146, 264004, 297223, 94694, 1757457, 576203, 8577828, 498382, 8478177, 123575, 4062389, 3001419, 196884, 617991, 421056, 3017627, 131936, 1152730, 2676649, 656678, 4519834, 201919, 56080, 2142553, 326263, 8172117, 2304253, 4761871, 205387, 6148422, 414559, 2893305, 2158562, 465972, 304078, 1841018, 1915571 };
    
    ofstream file("file.txt");

    //alokacija potrebnih resursa
    int f1, f2, e, min;
    float p, t;
    const int hmin = 1, hmax = 5;
    const float a = 0.95;
    int* x1 = (int*)calloc(numOfFiles, sizeof(int));
    int* x2 = (int*)calloc(numOfFiles, sizeof(int));
    int* bestx = (int*)calloc(numOfFiles, sizeof(int));
    int** f = (int**)calloc(numOfRuns, sizeof(int*));
    for(int i = 0; i < numOfRuns; i++)
        f[i] = (int*)calloc(numOfIterations*reannealingNum, sizeof(int));

    srand(time(NULL));

    //20 nezavisnih pokretanja
    for (int l = 0; l < numOfRuns; l++) {
        min = INT_MAX;

        //generisanje pocetnu tacku
        for (int i = 0; i < numOfFiles; i++) {
            x1[i] = rand() % 3;
        }
        f1 = fun(s, x1, numOfFiles);
        t = 64 * 1024 * 1024;

        //reannealing
        for (int k = 0; k < reannealingNum; k++) {
            //simulirano kaljenje
            for (int j = 0; j < numOfIterations; j++) {
                int h = ((hmin - hmax) / (numOfIterations - 1)) * (j - 1) + hmax;
                for (int i = 0; i < h; i++) {
                    int elem = rand() % numOfFiles;
                    int old = x2[elem];
                    while (old == x2[elem]) x2[elem] = rand() % 3;
                }

                f2 = fun(s, x2, numOfFiles);
                e = f2 - f1;
                if (e < 0) {
                    memcpy(x1, x2, sizeof(int) * numOfFiles);
                    f1 = f2;
                    if (f2 < min) {
                        min = f2;
                        memcpy(bestx, x2, sizeof(int) * numOfFiles);
                    }
                }
                else {
                    p = exp(-e / t);
                    float r = (float)rand() / (float)RAND_MAX;
                    if (r < p) {
                        memcpy(x1, x2, sizeof(int) * numOfFiles);
                        f1 = f2;
                    }
                    else memcpy(x2, x1, sizeof(int) * numOfFiles);
                }
                t = a * t;
                f[l][k*numOfIterations+j] = f1;
            }

        }
        printf("%d.\n", l);
        printf("x=(");
        for (int i = 0; i < numOfFiles - 1; i++) printf("%d, ", bestx[i]);
        printf("%d)\n", bestx[numOfFiles - 1]);
        printf("f(x)=%d\n\n", min);
    }

    //racunanje kumulativnog minimuma i cuvanje podataka u fajl
    for (int i = 0; i < numOfRuns; i++) {
        int cmin = f[i][0];
        for (int j = 1; j < numOfIterations * reannealingNum; j += 10) {
            if (f[i][j] < cmin) cmin = f[i][j];
            file << cmin << " ";
        }
        file << "\n";
    }

    free(x1);
    free(x2);
    free(bestx);
    for (int i = 0; i < numOfRuns; i++) free(f[i]);
    free(f);
    file.close();

    return 0;
}