#include "WrongSector.h"
#include <cmath>

void Segment::calculateLine() {
    x1 = xc + (int)(r * cos(aStart));
    y1 = yc - (int)(r * sin(aStart));
    x2 = xc + (int)(r * cos(aEnd));
    y2 = yc - (int)(r * sin(aEnd));
}

Segment::Sector(int xc, int yc, int r, double aStart, double aEnd, int x0, int y0, int R, int G, int B) : Line(0, 0, 0, 0, x0, y0, R, G, B),
MyArc (xc, yc, r, aStart, aEnd, x0, y0, R, G, B) {
    calculateLine();
}

void Segment::draw() {
    MyArc::draw();
    Line::draw();
}

void Segment::shade() {
    MyArc::shade();
    Line::shade();
}

void Segment::move(int dx, int dy) {
    MyArc::move(dx, dy);
    Line::move(dx, dy);
}