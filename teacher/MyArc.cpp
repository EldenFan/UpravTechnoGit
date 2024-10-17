#include "MyArc.h"
#include "VSTUB.H"
MyArc::MyArc(int xc, int yc, int r, double a1, double a2, int x0, int y0, int R, int G, int B) : BasePoint(x0, y0, R, G, B) {
	this->xc = xc;
	this->yc = yc;
	this->r = r;
	aStart = a1;
	aEnd = a2;
 }

void MyArc::draw() {
	std::setcolor(colorR, colorG, colorB);
	std::putarc(xc + x0, yc + y0, r, aStart, aEnd - aStart);
}

void MyArc::shade() {
	std::setcolor(0, 0, 0);
	std::putarc(xc + x0, yc + y0, r, aStart, aEnd - aStart);
}