#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <random>
#include <time.h>

double fopt(double p[6][3], double s1[], double s2[]) {
	double sum = 0;
	for (int i = 0; i < 3; i++) {
		sum += sqrt( pow(s1[0] - p[i][0], 2) + pow(s1[1] - p[i][1], 2) + pow(s1[2] - p[i][2], 2));		 
	}
	for (int i = 3; i < 6; i++) {
		sum += sqrt(pow(s2[0] - p[i][0], 2) + pow(s2[1] - p[i][1], 2) + pow(s2[2] - p[i][2], 2));
	}
	sum += sqrt(pow(s2[0] - s1[0], 2) + pow(s2[1] - s1[1], 2) + pow(s2[2] - s1[2], 2));
	return sum;
}

int main() {
	const int D = 3;
	double p[6][D] = { {1, 4, 0}, {3, 2, 0}, {2, 7, 1}, {6, 3, 3}, {7, 6, 5}, {5, 7, 4}};

	int const Nagents = 50;
	double gbest_res = INT_MAX;
	double* pbest_res = (double*)malloc(Nagents * sizeof(double));
	double w = 0.729;
	double c1 = 1.494, c2 = 1.494;
	double vmax = 0.2;

	double** s = (double**)malloc(Nagents * sizeof(double*));
	double** v = (double**)malloc(Nagents * sizeof(double*));
	double** v_prev = (double**)malloc(Nagents * sizeof(double*));
	double** pbest = (double**)malloc(Nagents * sizeof(double*));
	double* gbest = (double*)malloc(2*D*sizeof(double));
	for (int i = 0; i < Nagents; i++) {
		s[i] = (double*)malloc(2 * D * sizeof(double));
		v[i] = (double*)malloc(2 * D * sizeof(double));
		v_prev[i] = (double*)malloc(2 * D * sizeof(double));
		pbest[i] = (double*)malloc(2 * D * sizeof(double));
		for (int j = 0; j < 2*D; j++) {
			s[i][j] = rand() % 10;
			v_prev[i][j] = 1;
		}
		pbest_res[i] = fopt(p, s[i], s[i]+D);
		memcpy(pbest[i], s[i], sizeof(double) * 2 * D);
		if (pbest_res[i] < gbest_res) {
			gbest_res = pbest_res[i];
			memcpy(gbest, s[i], sizeof(double) * 2 * D);
		}
	}
	
	srand(time(0));
	int k;

	for (k = 0; k < 1000; k++) {
		for (int i = 0; i < Nagents; i++) {
			for (int j = 0; j < 2*D; j++) {
				v[i][j] = w * v_prev[i][j] + c1 * (rand()/(float)RAND_MAX) * (pbest[i][j] - s[i][j]) + c2 * (rand()/(float)RAND_MAX) * (gbest[j] - s[i][j]);
				if (v[i][j] < vmax) s[i][j] += v[i][j];
				else s[i][j] += vmax;
				v_prev[i][j] = v[i][j];
			}
			double f = fopt(p, s[i], s[i] + D);
			if (f < pbest_res[i]) {
				pbest_res[i] = f;
				memcpy(pbest[i], s[i], sizeof(double) * 2 * D);
			}
			if (f < gbest_res) {
				gbest_res = f;
				memcpy(gbest, s[i], sizeof(double) * 2 * D);
			}
		}
	}

	printf("Razdaljina: %.10lf\nTacke: ", gbest_res);
	for (int i = 0; i < 2 * D; i++) printf("%.10lf ", gbest[i]);

}
