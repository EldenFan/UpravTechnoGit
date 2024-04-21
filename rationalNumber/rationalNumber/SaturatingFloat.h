#pragma once
#include "myFloat.h"
class SaturatingFloat : public MyFloat
{
private: 
	bool isSaturaded;
	void Saturaded();
public:
	bool GetIsSaturaded();
	SaturatingFloat(MyFloat, bool);
	void Print();
	SaturatingFloat(double);
};

SaturatingFloat operator+(SaturatingFloat, SaturatingFloat);
SaturatingFloat operator-(SaturatingFloat, SaturatingFloat);
SaturatingFloat operator*(SaturatingFloat, SaturatingFloat);
SaturatingFloat operator/(SaturatingFloat, SaturatingFloat);

