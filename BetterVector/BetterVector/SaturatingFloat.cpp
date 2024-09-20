#include "SaturatingFloat.h"
#include <stdio.h>
#include <cmath>
#define MAX 999999

void SaturatingFloat::Saturaded(bool isOverflow)
{
	isSaturaded = isOverflow;
	if (n > MAX)
	{
		n = MAX;
		isSaturaded = true;
	}
	else if (n < (-1 * MAX))
	{
		n = -MAX;
		isSaturaded = true;
	}
	if (d > MAX)
	{
		d = MAX;
		isSaturaded = true;
	}
	else if (d < (-1 * MAX))
	{
		d = -MAX;
		isSaturaded = true;
	}
}

SaturatingFloat::SaturatingFloat() : MyFloat(0) {
	Saturaded(false);
}

SaturatingFloat::SaturatingFloat(double x) : MyFloat(x)
{
	Saturaded(false);
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
	return SaturatingFloat((MyFloat)a + (MyFloat)b, a.GetIsSaturaded() || b.GetIsSaturaded());
}

SaturatingFloat operator-(SaturatingFloat a, SaturatingFloat b)
{
	return SaturatingFloat((MyFloat)a - (MyFloat)b, a.GetIsSaturaded() || b.GetIsSaturaded());
}

SaturatingFloat operator*(SaturatingFloat a, SaturatingFloat b)
{
	return SaturatingFloat((MyFloat)a * (MyFloat)b, a.GetIsSaturaded() || b.GetIsSaturaded());
}

SaturatingFloat operator /(SaturatingFloat a, SaturatingFloat b)
{
	return SaturatingFloat((MyFloat)a / (MyFloat)b, a.GetIsSaturaded() || b.GetIsSaturaded());
}

void SaturatingFloat::Print()
{
	if (isSaturaded)
	{
		printf("*");
	}
	MyFloat::Print();
}

SaturatingFloat::SaturatingFloat(const SaturatingFloat& another) : MyFloat(another.n, another.d) {
	isSaturaded = another.isSaturaded;
}

bool operator !=(SaturatingFloat a, SaturatingFloat b) {
	if ((MyFloat)a != (MyFloat)b) return true;
	if (a.GetIsSaturaded() != b.GetIsSaturaded()) return true;
	return false;
}
