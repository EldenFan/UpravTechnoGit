#include "Sector.h"
#include <cmath>

void Sector::calculateLines() {
	int x1 = MyArc::x0 + xc + static_cast<int>(r * cos(aStart));
	int y1 = MyArc::y0 + yc - static_cast<int>(r * sin(aStart));
	int x2 = MyArc::x0 + xc + static_cast<int>(r * cos(aEnd));
	int y2 = MyArc::y0 + yc - static_cast<int>(r * sin(aEnd));
	line1.setCoordinates(x1, y1, xc, yc);
	line2.setCoordinates(x2, y2, xc, yc);
}

Sector::Sector(int xc, int yc, int r, double aStart, double aEnd, int x0, int y0, int R, int G, int B) : MyArc(xc, yc, r, aStart, aEnd, x0, y0, R, G, B),
line1(0, 0, 0, 0, x0, y0, R, G, B), line2(0, 0, 0, 0, x0, y0, R, G, B) {
	calculateLines();
}

void Sector::draw() {
	MyArc::draw();
	line1.draw();
	line2.draw();
}

void Sector::shade() {
	MyArc::shade();
	line1.shade();
	line2.shade();
}

void Sector::move(int dx, int dy) {
	MyArc::move(dx, dy);
	line1.move(dx, dy);
	line2.move(dx, dy);
}