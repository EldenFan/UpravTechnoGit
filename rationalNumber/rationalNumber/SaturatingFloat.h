#include "myFloat.h"
class SaturatingFloat : public MyFloat
{
private: 
	bool isSaturaded;
	void Saturaded(bool);
public:
	bool GetIsSaturaded();
	SaturatingFloat(MyFloat, bool);
	SaturatingFloat(double);
	void Print();
	void Println();
};

SaturatingFloat operator+(SaturatingFloat, SaturatingFloat);

SaturatingFloat operator-(SaturatingFloat, SaturatingFloat);

SaturatingFloat operator*(SaturatingFloat, SaturatingFloat);

SaturatingFloat operator/(SaturatingFloat, SaturatingFloat);

