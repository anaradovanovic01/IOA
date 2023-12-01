#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
using namespace std;

double f_opt1(double a, double b, double S) {
	double z0 = b / 2 + 0.01;
	return -0.5 * sqrt(M_PI/(4*S)) * ((z0+b/2)/(sqrt(pow(a,2)+pow(z0+b/2,2))) - (z0-b/2)/(sqrt(pow(a, 2) + pow(z0-b/2, 2))));
}

double f_opt2(double a, double b, double S) {
	return (2 * M_PI * a * b) / (S * 58e6) * sqrt( M_PI / (4*S) );
}

double randfrom(double min, double max) {
	double range = (max - min);
	double div = RAND_MAX / range;
	return min + (rand() / div);
}

int main() {
	const int N = pow(10, 6);
	double* a = (double*)malloc(N * sizeof(double));
	double* b = (double*)malloc(N * sizeof(double));
	double* S = (double*)malloc(N * sizeof(double));
	double* f1 = (double*)malloc(N * sizeof(double));
	double* f2 = (double*)malloc(N * sizeof(double));

	ofstream file("file.txt");
	srand(time(0));
	
	for (int i = 0; i < N; i++) {
		a[i] = randfrom(0.01, 5 * 0.01);
		b[i] = randfrom(0.1, 0.4);
		S[i] = randfrom(0.5e-6, 3e-6);
		f1[i] = f_opt1(a[i], b[i], S[i]);
		f2[i] = f_opt2(a[i], b[i], S[i]);
	}

	for (int i = 0; i < N; i++) {
		int flag = 1;
		for (int j = 0; j < N; j++) {
			if (i != j && f1[i] >= f1[j] && f2[i] >= f2[j]) {
				flag = 0;
				break;
			}
		}
		file << -f1[i] << " " << f2[i] << " " << flag << "\n";
	}

	free(a);
	free(b);
	free(S);
	free(f1);
	free(f2);
	file.close();
}