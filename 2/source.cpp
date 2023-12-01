#include <iostream>
#include <math.h>
#include <limits>
#include <algorithm>
using namespace std;

void f(int n, float x[], float y[], float d[12][12]) {
    float s, min = numeric_limits<float>::max();
    int index[12]{}, found[10][12]{}, cnt = 0;
    for (int i = 0; i < n; i++) index[i] = i;
    while (next_permutation(index, index + n)) {
        s = 0;
        for (int i = 0; i < n - 1; i++) {
            s += d[index[i]][index[i + 1]];
        }
        if (s <= min) {
            if (min > s) cnt = 0;
            min = s;
            for (int j = 0; j < n; j++) found[cnt][j] = index[j];
            cnt++;
        }
    }
    cout << "Minimalna putanja za " << n << " tacaka je " << min << ".\n";
    cout << "Putanje su: ";
    for (int i = 0; i < cnt; i++) {
        cout << "\n   ";
        for (int j = 0; j < n; j++) {
            cout << found[i][j]+1;
            if (j != n - 1) cout << "->";
        }
    }
    cout << "\n";
}

int main() {

    float x[] = { 62.0, 57.5, 51.7, 67.9, 57.7, 54.2, 46.0, 34.7, 45.7, 34.7, 28.4, 33.4 };
    float y[] = { 58.4, 56.0, 56.0, 19.6, 42.1, 29.1, 45.1, 45.1, 25.1, 26.4, 31.7, 60.5 };
    
    float p[12][2] = { {62.0, 58.4}, {57.5, 56.0}, {51.7, 56.0}, {67.9, 19.6}, {57.7, 42.1}, {54.2, 29.1}, {46.0, 45.1},
        {34.7, 45.1}, {45.7, 25.1}, {34.7, 26.4}, {28.4, 31.7}, {33.4, 60.5} };
    
    float d[12][12];

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            d[i][j] = sqrt(pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2));
        }
    }

    f(8, x, y, d);
    cout << "\n";
    f(12, x, y, d);
}