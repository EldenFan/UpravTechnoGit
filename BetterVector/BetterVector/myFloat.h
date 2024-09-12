#pragma once

class MyFloat 
{
protected:
	int n, d;
	void Norm();
public:
	MyFloat(double);
	MyFloat(int, int);
	MyFloat(const MyFloat&);
	MyFloat& operator=(const MyFloat&);
	int GetNum();
	int GetDen();
	void Print();
};

MyFloat operator +(MyFloat, MyFloat);

MyFloat operator -(MyFloat, MyFloat);

MyFloat operator *(MyFloat, MyFloat);

MyFloat operator /(MyFloat, MyFloat);

MyFloat operator +(MyFloat, double);

MyFloat operator -(MyFloat, double);

MyFloat operator *(MyFloat, double);

MyFloat operator /(MyFloat, double);

bool operator !=(MyFloat, MyFloat);

