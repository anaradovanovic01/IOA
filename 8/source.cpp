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

void sortByF(int* x[], int f[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (f[i] > f[j]) {
                int* t = x[i];
                x[i] = x[j];
                x[j] = t;
                int p = f[i];
                f[i] = f[j];
                f[j] = p;
            }
        }
    }
}

int main() {
    const int populationSize = 20000;
    const int numOfGenerations = 50;
    const int numOfFiles = 64;
    const int N = 20;
    int s[] = { 173669, 275487, 1197613, 1549805, 502334, 217684, 1796841, 274708, 631252, 148665, 150254, 4784408, 344759, 440109, 4198037, 329673, 28602, 144173, 1461469, 187895, 369313, 959307, 1482335, 2772513, 1313997, 254845, 486167, 2667146, 264004, 297223, 94694, 1757457, 576203, 8577828, 498382, 8478177, 123575, 4062389, 3001419, 196884, 617991, 421056, 3017627, 131936, 1152730, 2676649, 656678, 4519834, 201919, 56080, 2142553, 326263, 8172117, 2304253, 4761871, 205387, 6148422, 414559, 2893305, 2158562, 465972, 304078, 1841018, 1915571 };
    int min[20];
    ofstream file("file.txt");

    //alokacija potrebnih resursa
    int** x = (int**)calloc(populationSize, sizeof(int*));
    for (int i = 0; i < populationSize; i++)
        x[i] = (int*)calloc(numOfFiles, sizeof(int));
    int* f = (int*)calloc(populationSize, sizeof(int));
    int** minx = (int**)calloc(N, sizeof(int*));
    for (int i = 0; i < N; i++)
        minx[i] = (int*)calloc(numOfFiles, sizeof(int));

    srand(time(NULL));
    
    //20 nezavisnih pokretanja
    for (int l = 0; l < N; l++) {
       
        //generisanje pocetne populacije
        for (int i = 0; i < populationSize; i++) {
            for (int j = 0; j < numOfFiles; j++) {
                x[i][j] = rand() % 3;
            }
        }

        //geneticki algoritam
        for (int k = 0; k < numOfGenerations; k++) {

            //racunanje optimizacione funkcije
            for (int i = 0; i < populationSize; i++)
                f[i] = fun(s, x[i], numOfFiles);

            //selekcija
            sortByF(x, f, populationSize);
            file << f[0] << ",";
            int numOfSelected = 2000;

            //ukrstanje
            for (int i = numOfSelected; i < populationSize; i++) {
                int i1 = rand() % numOfSelected;
                int i2 = rand() % numOfSelected;
                int p = rand() % numOfFiles;
                for (int j = 0; j < p; j++) x[i][j] = x[i1][j];
                for (int j = p; j < numOfFiles; j++) x[i][j] = x[i2][j];
            }

            //mutacije
            float probabilityOfMutation = 0.1;
            for (int i = 0; i < populationSize; i++) {
                float p = (float)rand() / (float)RAND_MAX;
                if (p <= probabilityOfMutation) {
                    int num = rand() % numOfFiles;
                    int value;
                    do {
                        value = rand() % 3;
                    } while (x[i][num] == value);
                    x[i][num] = value;
                }
            }
        }
        
        sortByF(x, f, populationSize);
        memcpy(minx[l], x[0], sizeof(int) * numOfFiles);
        min[l] = f[0];
        printf("%d\n", min[l]);
        file << "\n";
    }

    //najbolje resenje
    int minimum = f[0], index = 0;
    for (int i = 1; i < N; i++) {
        if (min[i] < minimum) {
            index = i;
            minimum = min[i];
        }
    }
    printf("x=(");
    for (int i = 0; i < numOfFiles - 1; i++) printf("%d, ", minx[index][i]);
    printf("%d)\n", minx[index][numOfFiles-1]);
    printf("f(x)=%d", min[index]);


    for (int i = 0; i < populationSize; i++) free(x[i]);
    free(x);
    free(f);
    for (int i = 0; i < N; i++) free(minx[i]);
    free(minx);
    file.close();
    
    return 0;
}