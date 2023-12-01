#include <iostream>
#include <time.h>
using namespace std;

int a() {
	int a, b, c, d;
	unsigned long cnt = 0;
	time_t t1, t2;
	time(&t1);

	for (a = 1; a < 777; a++) {
		for (b = 1; b < 777; b++)
			for (c = 1; c < 777; c++)
				for (d = 1; d < 777; d++) {
					if (a + b + c + d == 777 && a*b*c*d == 777000000) {
						time(&t2);
						cout << "a) Brojevi su: " << a/100.0 << ", " << b/100.0 << ", " << c/100.0 << ", " << d/100.0 << ".\n";
						cout << "   Broj iteracija je " << cnt << ".\n";
						cout << "   Vreme za koje se program izvrsio je " << t2 - t1 << "s.\n\n";
						return 1;
					}
					cnt++;
				}
	}

	return 0;
}

int b() {
	double a, b, c, d;
	unsigned long cnt = 0;
	time_t t1, t2;
	time(&t1);
	
	for (b = 1; b < 777; b++)
		for (c = 1; c < 777; c++)
			for (d = 1; d < 777; d++) {
				a = 777 - b - c - d;
				if (a + b + c + d == 777 && a*b*c*d == 777000000) {
					time(&t2);
					cout << "b) Brojevi su: " << a/100.0 << ", " << b/100.0 << ", " << c/100.0 << ", " << d/100.0 << ".\n";
					cout << "   Broj iteracija je " << cnt << ".\n";
					cout << "   Vreme za koje se program izvrsio je " << t2 - t1 << "s.\n\n";
					return 1;
				}
				cnt++;
			}
	return 0;
}

int main()
{
	a();
	b();
}
