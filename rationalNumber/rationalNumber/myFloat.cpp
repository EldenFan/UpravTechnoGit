#include "myFloat.h"
#include <stdio.h>
#define N 100000 //точность сохранения числа
#define LEN 8 //количество простых чисел, на которое проверяется
#define MAXINTEGERPART 9999 //Максимально сохраняемая целая часть числа
#define MAX  MAXINTEGERPART * N

MyFloat::MyFloat(double x)
{
	if ((x > 0) && ((int)x <= MAXINTEGERPART) || (x < 0) && ((int)-1 * x <= MAXINTEGERPART))
	{
		n = (int)x * N;
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
	printf("%d/%d\t%f\n", n, d, (double)n/d);
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
	if (isOverfllowMult(x.GetNum(), y.GetDen()))
	{
		firstNum = MAX;
		isOverflow = true;
	}
	else
	{
		firstNum = x.GetNum() * y.GetDen();
	}
	if (isOverfllowMult(y.GetNum(), x.GetDen()))
	{
		secondNum = MAX;
		isOverflow = true;
	}
	else
	{
		secondNum = y.GetNum() * x.GetDen();
	}
	if (isOverfllowMult(x.GetDen(), y.GetDen()))
	{
		denum = MAX;
		isOverflow = true;
	}
	else
	{
		denum = x.GetDen() * y.GetDen();
	}
	if (isOverflowSum(firstNum, secondNum))
	{
		num = firstNum + secondNum;
	}
	else
	{
		num = MAX;
	}
}

MyFloat operator -(MyFloat x, MyFloat y)
{
	y = MyFloat(-1 * y.GetNum(), y.GetDen(), y.GetIsSaturaded());
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

bool isOverfllowMult(int a, int b)
{
	bool res = true;
	if ((a > 0 && b > 0) || (a < 0 && b < 0))
	{
		if (a > MAX / b)
		{
			res = false;
		}
	}
	else
	{
		if (a < MAX / b)
		{
			res = false;
		}
	}
	return res;
}

bool isOverflowSum(int a, int b)
{
	bool res = true;
	if (((b > 0) && (a > MAX - b)) || ((b < 0) && (a < MAX - b)))
	{
		res = false;
	}
	return res;
}
