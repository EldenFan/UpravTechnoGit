#include "SaturatingFloat.h"

int main()
{
	double first = 99.0, second = 99.0;

	SaturatingFloat x = first;
	SaturatingFloat y = second;
	x.Print();
	SaturatingFloat c = x * y;
	c.Print();
	c = x + y;
	c.Print();
	c = x - y;
	c.Print();
	c = x / y;
	c.Print();
	return 0;
}