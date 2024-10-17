#include "Segment.h"
#include <cmath>

void Segment::calculateLine() {
    x1 = MyArc::x0 + xc + static_cast<int>(r * cos(aStart));
    y1 = MyArc::y0 + yc - static_cast<int>(r * sin(aStart));
    x2 = MyArc::x0 + xc + static_cast<int>(r * cos(aEnd));
    y2 = MyArc::y0 + yc - static_cast<int>(r * sin(aEnd));
}

Segment::Segment(int xc, int yc, int r, double aStart, double aEnd, int x0, int y0, int R, int G, int B) : Line(0, 0, 0, 0, x0, y0, R, G, B),
MyArc(xc, yc, r, aStart, aEnd, x0, y0, R, G, B) {
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
    shade();
    MyArc::BasePoint::x0 += dx;
    MyArc::BasePoint::y0 += dy;
    Line::BasePoint::x0 += dx;
    Line::BasePoint::y0 += dy;
    draw();
}
