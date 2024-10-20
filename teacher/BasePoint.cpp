#include "BasePoint.h"
#include "VSTUB.H"

BasePoint::BasePoint(int x, int y, int R, int G, int B) {
	x0 = x;
	y0 = y;
	colorR = R;
	colorG = G;
	colorB = B;
}

void BasePoint::move(int dx, int dy) {
		shade();
		Sleep(10);
		x0 += dx;
		y0 += dy;
		draw();
		Sleep(10);
}
