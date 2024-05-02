#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int a, b, c, d;
int* pa = &a, * pb = &b, * pc = &c, * pd = &d;



int gri(void) {
	int t = (rand() * 1000.0) / RAND_MAX;
	return t;
}

void initRng(void) {
	time_t curtime;
	time(&curtime);
	srand((unsigned int)curtime);
}

void main() {
	initRng();
	a = gri(); b = gri(); c = gri(); d = gri();


	printf("\n%d,%d,%d,%d", a, b, c, d);
	printf("\n%d,%d,%d,%d", *pa, *pb, *pc, *pd);
	printf("\n%d,%d,%d,%d", pa, pb, pc, pd);
	//start sorter
	int* pt;
	char sorted = 1;
	do {
		sorted = 1;
		if (*pa > *pb) {
			pt = pa; pa = pb; pb = pt;
			sorted = 0;
		}
		if (*pb > *pc) {
			pt = pb; pb = pc; pc = pt;
			sorted = 0;
		}
		if (*pc > *pd) {
			pt = pc; pc = pd; pd = pt;
			sorted = 0;
		}
	} while (sorted == 0);
	//end sorter

	printf("\n\n%d,%d,%d,%d", *pa, *pb, *pc, *pd);
}


/*
+ переменная d и указатель к ней
менять указатели в 29 так, чтобы числа вышли в порядке возрастания или убывания

*/
