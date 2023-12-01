#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

double fun(float x_de[], float x[], float y[], float s[], int R0, int N) {
	if (sqrt(pow(x_de[0], 2) + pow(x_de[1], 2)) < R0 && sqrt(pow(x_de[2], 2) + pow(x_de[3], 2)) < R0) {
		float sum = 0;
		for (int i = 0; i < N; i++) {
			sum += pow( x_de[4] / sqrt(pow(x[i]-x_de[0], 2) + pow(y[i]-x_de[1], 2)) + x_de[5] / sqrt(pow(x[i] - x_de[2], 2) + pow(y[i] - x_de[3], 2)) -s[i], 2);
		}
		return sum;
	}
	else return 100;
}

int main() {

	const int N = 20, R0 = 15;
	float x[N], y[N];

	for (int i = 0; i < N; i++) {
		x[i] = R0 * cos(2 * i * M_PI / N);
		y[i] = R0 * sin(2 * i * M_PI / N);
	}
	float s[] = { 2.424595205726587e-01, 1.737226395065819e-01, 1.315612759386036e-01, 1.022985539042393e-01, 7.905975891960761e-02, 5.717509542148174e-02, 3.155886625106896e-02, -6.242228581847679e-03, -6.565183775481365e-02, -8.482380513926287e-02, -1.828677714588237e-02, 3.632382803076845e-02, 7.654845872485493e-02, 1.152250132891757e-01, 1.631742367154961e-01, 2.358469152696193e-01, 3.650430801728451e-01, 5.816044173713664e-01, 5.827732223753571e-01, 3.686942505423780e-01 };

	const int Npop = 50, D = 6;
	float F = 0.8, CR = 0.9;
	float upper = 15.0, lower = -15.0;
	srand(time(0));

	//alokacija
	float** x_de = (float**)calloc(Npop, sizeof(float*));
	for (int i = 0; i < Npop; i++)
		x_de[i] = (float*)calloc(D, sizeof(float));
	float** y_de = (float**)calloc(Npop, sizeof(float*));
	for (int i = 0; i < Npop; i++)
		y_de[i] = (float*)calloc(D, sizeof(float));

	//pocetne vrednosti
	//(x1, y1, x2, y2, A1, A2)
	for (int i = 0; i < Npop; i++) 
		for(int j = 0; j < D; j++)
			x_de[i][j] = (rand() / (float)RAND_MAX) * (upper - lower) + lower;

	double min = 100;
	float* min_arr = (float*)calloc(D, sizeof(float));

	//diferencijalna evolucija
	while (min > pow(10, -14)) { //for (int k = 0; k < Ngen; k++) {

		for (int i = 0; i < Npop; i++) {
			int a, b, c;
			do { a = rand() % Npop; } while (a == i);
			do { b = rand() % Npop; } while (b == i || b == a);
			do { c = rand() % Npop; } while (c == i || c == a || c == b);
			int R = rand() % D;

			for (int j = 0; j < D; j++) {
				float ri = rand() / (float)RAND_MAX;
				if (j == R || ri < CR)
					y_de[i][j] = x_de[a][j] + F * (x_de[b][j] - x_de[c][j]);
				else
					y_de[i][j] = x_de[i][j];
			}
		}
		for (int i = 0; i < Npop; i++) {
			double fx = fun(x_de[i], x, y, s, R0, N);
			double fy = fun(y_de[i], x, y, s, R0, N);
			if (fx < min) { min = fx; memcpy(min_arr, x_de[i], D * sizeof(float)); }
			if (fy < min) { min = fy; memcpy(min_arr, y_de[i], D * sizeof(float)); }
			if (fy < fx) {
				memcpy(x_de[i], y_de[i], D * sizeof(float));
			}
		}
	}

	printf("f(x) = %.20lf\nx = (", min);
	for (int i = 0; i < D-1; i++) printf("%.10f, ", min_arr[i]);
	printf("%.10f)", min_arr[D-1]);

	//dealokacija
	for (int i = 0; i < Npop; i++) free(x_de[i]);
	free(x_de);
	for (int i = 0; i < Npop; i++) free(y_de[i]);
	free(y_de);
	free(min_arr);

}