#pragma once
#include "BasePoint.h"
#include "Object.h"
class MyArc : public BasePoint, virtual public Object {
protected:
	int xc, yc;
	int r;
	double aStart, aEnd;
public:
	MyArc(int, int, int, double, double, int = 0, int = 0, int = 0, int = 0, int = 0);
	MyArc(const MyArc&) = default;
	void draw() override;
	void shade() override;
};

