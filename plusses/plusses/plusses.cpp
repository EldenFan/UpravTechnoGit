#include <iostream>
#include "complex.h"

int main() {
	const complex i(0, 1);
	const double pi = 3.14;
	double L = 0.03, R = 5000, C = 0.000002, freg = 50, omg = 2 * pi * freg;
	complex I = 0.01, Z, U;
	Z = R + i * omg * L + (1 / (i * omg * C));
	U = Z * I;
	U.print();
	return 1;
}