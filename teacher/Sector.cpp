#include "Sector.h"
#include <cmath>

void Sector::calculateLines() {
	Line::x1 = MyArc::x0 + xc + static_cast<int>(r * cos(aStart));
	Line::y1 = MyArc::y0 + yc - static_cast<int>(r * sin(aStart));
	FakeLine::x2 = MyArc::x0 + xc + static_cast<int>(r * cos(aEnd));
	FakeLine::y2 = MyArc::y0 + yc - static_cast<int>(r * sin(aEnd));
}

Sector::Sector(int xc, int yc, int r, double aStart, double aEnd, int x0, int y0, int R, int G, int B) : MyArc(xc, yc, r, aStart, aEnd, x0, y0, R, G, B),
Line(0, 0, xc, yc, x0, y0, R, G, B), FakeLine(xc, yc, 0, 0, x0, y0, R, G, B),
BasePoint(x0, y0, R, G, B){
	calculateLines();
}

void Sector::draw() {
	MyArc::draw();
	Line::draw();
	FakeLine::draw();
}

void Sector::shade() {
	MyArc::shade();
	Line::shade();
	FakeLine::shade();
}