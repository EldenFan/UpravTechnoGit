#pragma once
#include "myFloat.h"
class SaturatingFloat : public MyFloat {
private: 
	bool isSaturaded;
	void Saturaded(bool);
public:
	bool GetIsSaturaded();
	SaturatingFloat(MyFloat, bool);
	SaturatingFloat();
	void Print();
	SaturatingFloat(double);
	SaturatingFloat(const SaturatingFloat&);
};

SaturatingFloat operator+(SaturatingFloat, SaturatingFloat);
SaturatingFloat operator-(SaturatingFloat, SaturatingFloat);
SaturatingFloat operator*(SaturatingFloat, SaturatingFloat);
SaturatingFloat operator/(SaturatingFloat, SaturatingFloat);
bool operator!=(SaturatingFloat, SaturatingFloat);

