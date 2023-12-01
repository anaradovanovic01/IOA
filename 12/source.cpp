#include <random>
#include <stdio.h>

unsigned random() {
    unsigned num = 0, ones = 16, zeros = 16;
    while (ones != 0 && zeros != 0) {
        num <<= 1;
        int p = rand() % 2;
        num += p;
        if (p) ones--;
        else zeros--;
    }
    if (zeros)
        num <<= zeros;
    else
        for (int i = 0; i < ones; i++) {
            num <<= 1;
            num += 1;
        }
    num &= 0x7FFFFFFF;
    return num;
}

int countOnes(unsigned x) {
    int cnt = 0;
    for (int i = 0; i < 31; i++) {
        if (x & 1) cnt++;
        x >>= 1;
    }
    return cnt;
}

int countZeros(unsigned x) {
    int cnt = 0;
    for (int i = 0; i < 31; i++) {
        if (!(x & 1)) cnt++;
        x >>= 1;
    }
    return cnt;
}

int difference(unsigned x0, unsigned x) {
    int same = 0, diff = 0;
    for (int i = 0; i < 31; i++) {
        if ((x0 & 1) == (x & 1)) same++;
        else diff++;
        x >>= 1;
        x0 >>= 1;
    }
    return same - diff;
}

unsigned cyclicShiftRight(unsigned x) {
    unsigned b = x & 1;
    x >>= 1;
    if (b) {
        b <<= 30;
        x += b;
    }
    return x;
}

int croscorrelation(unsigned x0, unsigned x) {
    int k, sum = 0;
    for (int i = 0; i < 31; i++) {
        k = difference(x0, x);
        if (k <= -4) k = abs(k + 3);
        else if (k >= 6) k = k - 5;
        else k = 0;
        sum += k;
        x0 = cyclicShiftRight(x0);
    }
    return sum;
}

int autocorrelation(unsigned x) {
    int a, sum = 0;
    unsigned x2 = x >> 1;
    for (int i = 1; i < 31; i++) {
        a = difference(x, x2);
        if (a <= -18) a = abs(a + 17);
        else if (a >= 12) a = a - 11;
        else a = 0;
        sum += a;
        x2 = cyclicShiftRight(x2);
    }
    return sum;
}

int fun(unsigned x0, unsigned x) {
    if (abs(countOnes(x) - countZeros(x)) != 1) return 100;
    return croscorrelation(x0, x) + autocorrelation(x);
}

void sort(unsigned x[], int f[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (f[i] > f[j]) {
                int t = x[i];
                x[i] = x[j];
                x[j] = t;
                int p = f[i];
                f[i] = f[j];
                f[j] = p;
            }
        }
    }
}

unsigned crossover(unsigned x1, unsigned x2, int p) {
    unsigned mask1, mask2;
    mask1 = 0xFFFFFFFF << (p + 1);
    mask2 = ~mask1;
    x1 &= mask1;
    x2 &= mask2;
    return x1 + x2;
}

unsigned changeBit(unsigned x, int b) {
    if ((x & (1 << (b))) != 0)
        x &= ~(1 << b);
    else
        x |= 1 << b;
    return x;
}

void printBinary(unsigned x) {
    for (int i = 0; i < 32; i++) {
        printf("%u", (x & (1 << 31)) >> 31);
        x <<= 1;
    }
    printf("\n");
}

int main() {
    const int populationSize = 20000;
    const int numOfGenerations = 50;
    const int N = 20;

    unsigned x0 = 0b1010000100011011000011001110011;

    srand(time(0));

    unsigned* x = (unsigned*)calloc(populationSize, sizeof(unsigned));
    int* f = (int*)calloc(populationSize, sizeof(int));

    int k;
    for (int i = 0; i < populationSize; i++)
        x[i] = random();

    //geneticki algoritam
    for (k = 0; k < numOfGenerations; k++) {

        //racunanje optimizacione funkcije
        for (int i = 0; i < populationSize; i++)
            f[i] = fun(x0, x[i]);

        //selekcija
        sort(x, f, populationSize);
        if (f[0] == 0) break;
        int numOfSelected = 1000;

        //ukrstanje
        for (int i = numOfSelected; i < populationSize; i++) {
            int i1 = rand() % numOfSelected;
            int i2 = rand() % numOfSelected;
            int p = rand() % 31;
            x[i] = crossover(x[i1], x[i2], p);
        }

        //mutacije
        float probabilityOfMutation = 0.1;
        for (int i = 0; i < populationSize; i++) {
            float p = (float)rand() / (float)RAND_MAX;
            if (p <= probabilityOfMutation) {
                int b = rand() % 31;
                x[i] = changeBit(x[i], b);
            }
        }
    }

    for (int i = 0; i < populationSize; i++)
        f[i] = fun(x0, x[i]);
    sort(x, f, populationSize);
    printf("f(x) = %d\nx = %u\nx = ", f[0], x[0]);
    printBinary(x[0]);

    free(x);
    free(f);

    return 0;
}