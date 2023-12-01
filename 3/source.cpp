#include <stdio.h>
#include <limits>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void sequenceToSpanningTree(int* p, int len, int* t);

void variations_with_repetition(int n, int k, int** m) {
	int q;
	unsigned min = numeric_limits<unsigned>::max(), curr;
	int* p = new int[k];
	int* g = new int[k+1];
	int* t = new int[2 * (k + 1)];
	int* min_tree = new int[2 * (k + 1)];

	for (int i = 0; i < k; i++) p[i] = 1;
	do {
		sequenceToSpanningTree(p, k, t);
		curr = 0;
		for (int i = 0; i < k + 1; i++) g[i] = 0;
		for (int i = 0; i < 2 * (k + 1); i++) g[t[i]-1]++;
		for (int i = 0; i < k+1; i++) {
			curr += m[t[2 * i]-1][t[2 * i + 1]-1];
		}
		for (int i = 0; i < n; i++) {
			if (g[i] > 4) curr += (g[i] - 3) * 250;
		}
		if (curr < min) {
			min = curr;
			for (int i = 0; i < 2*(k+1); i++)
				min_tree[i] = t[i];
		}

		q = k - 1;
		while (q >= 0) {
			p[q]++;
			if (p[q] == n) {
				p[q] = 1;
				q--;
			}
			else
				break;
		}
	} while (q >= 0);
	printf("%d\n", min);
	for (int i = 0; i < 2 * (k + 1); i++) {
		char c = min_tree[i] + 64;
		printf(" %c", c);
		if ((i + 1) % 2 == 0 && i < 2 * k)
			printf(" - ");
	}
	delete[] p;
	delete[] t;
	delete[] min_tree;
}

void sequenceToSpanningTree(int* p, int len, int* t) {
	int q = 0;
	int n = len + 2;
	int* v = new int[n];

	for (int i = 0; i < n; i++)
		v[i] = 0;
	for (int i = 0; i < len; i++)
		v[p[i] - 1] += 1;

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < n; j++) {
			if (v[j] == 0) {
				v[j] = -1;
				t[q++] = j + 1;
				t[q++] = p[i];
				v[p[i] - 1]--;
				break;
			}
		}
	}

	int j = 0;
	for (int i = 0; i < n; i++) {
		if (v[i] == 0 && j == 0) {
			t[q++] = i + 1;
			j++;
		}
		else if (v[i] == 0 && j == 1) {
			t[q++] = i + 1;
			break;
		}
	}
	delete[] v;
}

int main() {
	int** m = new int* [10];
	for (int i = 0; i < 10; i++) {
		m[i] = new int[10];
	}
	
	fstream file("tabela_cena.txt");

	if (!file.is_open()) return -1;

	string line;
	int cnt = 0;
	while (getline(file, line)) {
		for (int i = 0; i < 9; i++) {
			string num = line.substr(0, line.find(' '));
			line = line.substr(line.find(' ')+1);
			m[cnt][i] = stoi(num);
		}
		m[cnt][9] = stoi(line);
		cnt++;
	}
	file.close();

	variations_with_repetition(10, 8, m);
	
	for (int i = 0; i < 10; i++) {
		delete[] m[i];
	}
	delete[] m;
}