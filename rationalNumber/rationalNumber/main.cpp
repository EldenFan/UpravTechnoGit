#include "myFloat.h"

int main()
{
	double first = 9999.0, second = 9999.0;

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