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

MyFloat operator +(MyFloat x, MyFloat y);

MyFloat operator -(MyFloat x, MyFloat y);

MyFloat operator *(MyFloat x, MyFloat y);

MyFloat operator /(MyFloat x, MyFloat y);

MyFloat operator +(MyFloat x, double y);

MyFloat operator -(MyFloat x, double y);

MyFloat operator *(MyFloat x, double y);

MyFloat operator /(MyFloat x, double y);



