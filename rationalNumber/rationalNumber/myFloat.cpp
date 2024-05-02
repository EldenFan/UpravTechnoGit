#include "myFloat.h"
#include <stdio.h>

// Define a constant for the precision of the floating-point representation
#define N 100000 // precision of the floating-point representation

// Constructor for MyFloat class, takes a double value as input
MyFloat::MyFloat(double x)
{
	// Convert the double value to a rational number representation
	n = (int)(x * N);
	d = N;
	// Normalize the rational number representation
	Norm();
}

// Normalize the rational number representation by dividing out the greatest common divisor
void MyFloat::Norm()
{
	int gcd = gcdEuclid(n, d);
	n /= gcd;
	d /= gcd;
}

// Calculate the greatest common divisor using the Euclidean algorithm
int MyFloat::gcdEuclid(int a, int b)
{
	while (b != 0)
	{
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

// Print the MyFloat object in the format "numerator/denominator[decimal value]"
void MyFloat::Print()
{
	printf("%d/%d[%f]", n, d, (double)n / d);
}

void MyFloat::Println()
{
	printf("%d/%d[%f]\n", n, d, (double)n / d);
}

// Get the numerator of the MyFloat object
int MyFloat::GetNum()
{
	return n;
}

// Get the denominator of the MyFloat object
int MyFloat::GetDen()
{
	return d;
}

// Constructor for MyFloat class, takes a numerator and denominator as input
MyFloat::MyFloat(int num, int den)
{
	n = num;
	d = den;
	// Normalize the rational number representation
	Norm();
}

// Overload the + operator for MyFloat objects
MyFloat operator +(MyFloat x, MyFloat y)
{
	// Calculate the sum of the two MyFloat objects
	int num = x.GetNum() * y.GetDen() + y.GetNum() * x.GetDen();
	int den = y.GetDen() * x.GetDen();
	return MyFloat(num, den);
}

// Overload the - operator for MyFloat objects
MyFloat operator -(MyFloat x, MyFloat y)
{
	// Calculate the difference of the two MyFloat objects
	y = MyFloat(-1 * y.GetNum(), y.GetDen());
	return operator +(x, y);
}

// Overload the * operator for MyFloat objects
MyFloat operator *(MyFloat x, MyFloat y)
{
	// Calculate the product of the two MyFloat objects
	int num = x.GetNum() * y.GetNum();
	int den = y.GetDen() * x.GetDen();
	return MyFloat(num, den);
}

// Overload the / operator for MyFloat objects
MyFloat operator /(MyFloat x, MyFloat y)
{
	// Calculate the quotient of the two MyFloat objects
	y = MyFloat(y.GetDen(), y.GetNum());
	return operator*(x, y);
}
