#include "myFloat.h"
#include <stdio.h>
#include <cmath>
#define N 10000 //точность сохранения числа
#define LEN 8 //количество простых чисел, на которое проверяется
#define MAX  999999999 //Максимально сохраняемое число

bool CanMult(int a, int b)
{
	bool res = true;
	if (a != 0 && b != 0)
	{
		if (abs(a) > abs(MAX / b))
		{
			res = false;
		}
	}
	return res;
}

bool CanSum(int a, int b)
{
	bool res = true;
	if (abs(a) > MAX - abs(b))
	{
		res = false;
	}
	return res;
}

MyFloat::MyFloat(double x)
{
	if (abs(x) < (double)(MAX / N))
	{
		n = (int)(x * N);
		isSaturaded = false;
	}
	else
	{
		n = MAX;
		isSaturaded = true;
	}
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
	
	if (n < 0 && d < 0)
	{
		n *= -1;
		d *= -1;
	}
}

void MyFloat::Print()
{
	if (isSaturaded)
	{
		printf("Data can be incorrect because this is saturaded number ");
	}
	printf("%d/%d\t%f\n", n, d, (double)n / d);
}

int MyFloat::GetNum()
{
	return n;
}

int MyFloat::GetDen()
{
	return d;
}

MyFloat::MyFloat(int num, int den, bool isTooMuch)
{
	n = num;
	d = den;
	isSaturaded = isTooMuch;
	Norm();
}

bool MyFloat::GetIsSaturaded()
{
	return isSaturaded;
}

MyFloat operator +(MyFloat x, MyFloat y)
{
	bool isOverflow = x.GetIsSaturaded() || y.GetIsSaturaded();
	int firstNum;
	int secondNum;
	int denum;
	int num;
	if (CanMult(x.GetNum(), y.GetDen()))
	{
		firstNum = x.GetNum() * y.GetDen();
	}
	else
	{
		firstNum = MAX;
		isOverflow = true;
	}
	if (CanMult(y.GetNum(), x.GetDen()))
	{
		secondNum = y.GetNum() * x.GetDen();
	}
	else
	{
		secondNum = MAX;
		isOverflow = true;
	}
	if (CanMult(x.GetDen(), y.GetDen()))
	{
		denum = x.GetDen() * y.GetDen();
	}
	else
	{
		denum = MAX;
		isOverflow = true;
	}
	if (CanSum(firstNum, secondNum))
	{
		num = firstNum + secondNum;
	}
	else
	{
		num = MAX;
		isOverflow = true;
	}
	return MyFloat(num, denum, isOverflow);
}

MyFloat operator -(MyFloat x, MyFloat y)
{
	y = MyFloat(-1 * y.GetNum(), y.GetDen(), y.GetIsSaturaded());
	return operator +(x, y);
}

MyFloat operator *(MyFloat x, MyFloat y)
{
	int num;
	int den;
	bool isOverflow = x.GetIsSaturaded() || y.GetIsSaturaded();
	if (CanMult(x.GetNum(), y.GetNum()))
	{
		num = x.GetNum() * y.GetNum();
	}
	else
	{
		num = MAX;
		isOverflow = true;
	}
	if (CanMult(x.GetDen(), y.GetDen()))
	{
		den = x.GetDen() * y.GetDen();
	}
	else
	{
		den = MAX;
		isOverflow = true;
	}
	return MyFloat(num, den, isOverflow);
}

MyFloat operator /(MyFloat x, MyFloat y)
{
	y = MyFloat(y.GetDen(), y.GetNum(), y.GetIsSaturaded());
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
