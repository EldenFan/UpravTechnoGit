#include "Sector.h"
#include <cmath>

void Sector::calculateLine() {

}

Sector::Sector(int xc, int yc, int r, double aStart, double aEnd, int x0, int y0, int R, int G, int B) : Line(0, 0, 0, 0, x0, y0, R, G, B),
MyArc (xc, yc, r, aStart, aEnd, x0, y0, R, G, B) {
    calculateLine();
}

void Sector::draw() {
    MyArc::draw();
    Line::draw();
}

void Sector::shade() {
    MyArc::shade();
    Line::shade();
}