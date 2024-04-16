#include "myFloat.h"

int main()
{
	double first = 1000.0, second = 1.1;

	MyFloat x = MyFloat(first);
	x.Print();
	MyFloat c = x * second;
	c.Print();
	c = x + second;
	c.Print();
	c = x - second;
	c.Print();
	c = x / second;
	c.Print();
	return 0;
}