#include "SaturatingFloat.h"
#include <stdio.h>
#include<cmath>
#define N 100000
#define MAX 999999

void SaturatingFloat::Saturaded()
{
	if (n > MAX)
	{
		n = MAX;
		isSaturaded = true;
	}
	else
	{
		isSaturaded = false;
	}
}

SaturatingFloat::SaturatingFloat(double x) : MyFloat(x)
{
	Saturaded();
}

SaturatingFloat::SaturatingFloat(MyFloat a, bool isOverflow)
{
	n = a.GetNum();
	d = a.GetDen();
	isSaturaded = isOverflow;
	Saturaded();
}

bool SaturatingFloat::GetIsSaturaded()
{
	return isSaturaded;
}

SaturatingFloat operator+(SaturatingFloat a, SaturatingFloat b)
{
	bool isOverflow = a.GetIsSaturaded() || b.GetIsSaturaded();
	return SaturatingFloat((MyFloat)a + (MyFloat)b, isOverflow);
}

SaturatingFloat operator-(SaturatingFloat a, SaturatingFloat b)
{
	bool isOverflow = a.GetIsSaturaded() || b.GetIsSaturaded();
	return ((MyFloat)a - (MyFloat)b, isOverflow);
}

SaturatingFloat operator*(SaturatingFloat a, SaturatingFloat b)
{
	bool isOverflow = a.GetIsSaturaded() || b.GetIsSaturaded();
	return SaturatingFloat((MyFloat)a * (MyFloat)b, isOverflow);
}

SaturatingFloat operator /(SaturatingFloat a, SaturatingFloat b)
{
	bool isOverflow = a.GetIsSaturaded() || b.GetIsSaturaded();
	return SaturatingFloat((MyFloat)a / (MyFloat)b, isOverflow);
}

void SaturatingFloat::Print()
{
	if (isSaturaded)
	{
		printf("This number can be incorrect ");
	}
	printf("%d/%d\t%f\n", n, d, (double)n / d);
}
