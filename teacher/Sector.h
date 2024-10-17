#pragma once
#include "Line.h"
#include "MyArc.h"
class Sector : public MyArc, virtual public Object {
protected:
	Line line1;
	Line line2;
	void calculateLines();
public:
	Sector(int, int, int, double, double, int = 0, int = 0, int = 0, int = 0, int = 0);
	void draw();
	void shade();
	void move(int, int);
};

