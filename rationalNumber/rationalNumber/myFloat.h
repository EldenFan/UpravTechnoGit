#pragma once

class MyFloat 
{
private:
	int n, d;
	void Norm();
	bool isSaturaded;
	int maxNum;
public:
	MyFloat(double);
	MyFloat(int, int, bool);
	int GetNum();
	int GetDen();
	bool GetIsSaturaded();
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
