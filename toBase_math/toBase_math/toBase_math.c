#include <stdio.h>
#include <math.h>


int main(void) {
	int numb, base;
	int count = 1;
	int save, res;
	scanf("%d %d", &numb, &base);
	save = numb;
body:
	if (numb / base > 0) {
		count++;
		numb = numb / base;
		goto body;
	}
	printf("%d", numb);
	numb = pow(base, count);
result:
	count--;
	if (count > 0) {
		numb = pow(base, count - 1);
		numb = save / numb;
		res = numb % base;
		printf(".%d", res);
		goto result;
	}
	printf("\n");
	return 0;
}


