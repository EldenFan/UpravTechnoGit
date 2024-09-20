#include "myFloat.h"
#include "SaturatingFloat.h"
#include <stdio.h>
#define N 100000 //точность сохранения числа
#define LEN 8

MyFloat::MyFloat(double x)
{
	n = (int)(x * N);
	d = N;
	Norm();
}


void MyFloat::Norm()
{
	int arr[] = { 2, 3, 5, 7, 11, 13, 17, 19 };

	for (int i = 0; i < LEN; i++)
	{
		while ((n % arr[i] == 0) && (d % arr[i] == 0))
		{
			n /= arr[i];
			d /= arr[i];
		}
	}
}

void MyFloat::Print()
{
	printf("%d/%d[%f]", n, d, (double)n/d);
}

int MyFloat::GetNum()
{
	return n;
}

int MyFloat::GetDen()
{
	return d;
}

MyFloat::MyFloat(int num, int den)
{
	n = num;
	d = den;
	Norm();
}

MyFloat operator +(MyFloat x, MyFloat y)
{
	int num = x.GetNum() * y.GetDen() + y.GetNum() * x.GetDen();
	int den = y.GetDen() * x.GetDen();
	return MyFloat(num, den);
}

MyFloat operator -(MyFloat x, MyFloat y)
{
	y = MyFloat(-1 * y.GetNum(), y.GetDen());
	return operator +(x, y);
}

MyFloat operator *(MyFloat x, MyFloat y)
{
	int num = x.GetNum() * y.GetNum();
	int den = y.GetDen() * x.GetDen();
	return MyFloat(num, den);
}

MyFloat operator /(MyFloat x, MyFloat y)
{
	y = MyFloat(y.GetDen(), y.GetNum());
	return operator*(x, y);
}

MyFloat operator +(MyFloat x, double y)
{
	MyFloat yNew = MyFloat(y);
	return operator +(x, yNew);
}

MyFloat operator -(MyFloat x, double y)
{
	MyFloat yNew = MyFloat(y);
	return operator -(x, yNew);
}

MyFloat operator *(MyFloat x, double y)
{
	MyFloat yNew = MyFloat(y);
	return operator *(x, yNew);
}

MyFloat operator /(MyFloat x, double y)
{
	MyFloat yNew = MyFloat(y);
	return operator /(x, yNew);
}

MyFloat& MyFloat::operator= (const MyFloat& another) {
	n = another.n;
	d = another.d;
	return *this;
}

MyFloat::MyFloat(const MyFloat& another) {
	*this = another;
}

bool operator!=(MyFloat a, MyFloat b) {
	if (a.GetNum() == b.GetNum() && a.GetDen() == b.GetDen()) return false;
	return true;
}
