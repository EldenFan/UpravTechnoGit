#include "SaturatingFloat.h"
#include <stdio.h>
#include <cmath>
#define MAX 999999

void SaturatingFloat::Saturaded(bool isOverflow = false)
{
	isSaturaded = isOverflow;
	if (n > MAX)
	{
		n = MAX;
		isSaturaded = true;
	}
	if (d > MAX)
	{
		d = MAX;
		isSaturaded = true;
	}
}

SaturatingFloat::SaturatingFloat(double x) : MyFloat(x)
{
	Saturaded();
}

SaturatingFloat::SaturatingFloat(MyFloat a, bool isOverflow) : MyFloat(a)
{
	Saturaded(isOverflow);
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
