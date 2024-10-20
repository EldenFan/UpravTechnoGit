#include "Line.h"
#include "VSTUB.H"
Line::Line(int x1, int y1, int x2, int y2, int x0, int y0, int r, int g, int b) : BasePoint(x0, y0, r, g, b) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

void Line::draw() {
	std::setcolor(colorR, colorG, colorB);
	std::putline(x1 + x0, y1 + y0, x2 + x0, y2 + y0);
}

void Line::shade() {
	std::setcolor(0, 0, 0);
	std::putline(x1 + x0, y1 + y0, x2 + x0, y2 + y0);
}