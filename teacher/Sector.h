#pragma once
#include "Line.h"
#include "MyArc.h"
#include "FakeLine.h"
class Sector : public MyArc, virtual public Object, public Line, public FakeLine {
protected:
	void calculateLines();
public:
	Sector(int, int, int, double, double, int = 0, int = 0, int = 0, int = 0, int = 0);
	void draw();
	void shade();

};

