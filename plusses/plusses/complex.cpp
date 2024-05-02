#include <stdio.h>
#include "complex.h"
void complex::print(void) {
	printf("%f,%f\n", re, im);
}
complex operator+ (complex a1, complex a2) {
	return complex(a1.re + a2.re, a1.im + a2.im);
}
complex operator- (complex a1, complex a2) {
	return complex(a1.re - a2.re, a1.im - a2.im);
}
complex operator* (complex a1, complex a2) {
	return complex(a1.re * a2.re, a1.im * a2.im);
}
complex operator/ (complex a1, complex a2) {
	return complex(a1.re / a2.re, a1.im / a2.im);
}