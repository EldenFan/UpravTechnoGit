#pragma once
#include "Line.h"
#include "MyArc.h"
class Segment : public Line, public MyArc {
protected:
	void calculateLine();
public:
	Segment(int, int, int, double, double, int = 0, int = 0, int = 0, int = 0, int = 0);
	void draw() override;
	void shade() override;
};

