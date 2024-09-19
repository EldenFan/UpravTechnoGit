#pragma once
#include "BasePoint.h"
class Line : public BasePoint {
	int x1, y1, x2, y2;
public:
	Line(int, int, int, int, int = 0, int = 0, int = 0, int = 0, int = 0);
	Line(const Line&) = default;
	void draw() override;
	void shade() override;
};

