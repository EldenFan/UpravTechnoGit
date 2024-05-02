#include "SaturatingFloat.h"
#include <stdio.h>
#include "windows.h"

int main()
{
	MyFloat j(50, 2);
	MyFloat i(3.14);
	j.Print();
	printf("\t");
	i.Println();
	printf("\n");

	Sleep(5 * 1000);


	double first = 99.0, second = -99.0;

	SaturatingFloat x = first;
	SaturatingFloat y = second;
	x.Println();
	y.Println();
	SaturatingFloat c = x * y;
	c.Println();
	c = x + y;
	c.Println();
	c = x - y;
	c.Println();
	c = x / y;
	c.Println();
	c = x + y;

	Sleep(5 * 1000);

	while (!c.GetIsSaturaded())
	{
		c = c + y;
		c.Println(); 
	}
	c = c - y;
	c.Print();
	return 0;
}