#pragma once
#include "BasePoint.h"
class MyArc : public BasePoint
{
	int xc, yc;
	int r;
	double aStart, aEnd;
public:
	MyArc(int, int, int, double, double, int = 0, int = 0, int = 0, int = 0, int = 0);
	MyArc(const MyArc&) = default;
	void draw() override;
	void shade() override;
};

