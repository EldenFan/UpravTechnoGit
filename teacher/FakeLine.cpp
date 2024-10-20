#include "FakeLine.h"
 
FakeLine::FakeLine(int x1, int y1, int x2, int y2, int x0, int y0, int R, int G, int B) : Line(x1, y1, x2, y2, x0, y0, R, G, B), 
BasePoint(x0, y0, R, G, B) {
}