#include "vstub.h"
#include "Line.h"
#include "MyVector.h"
#include "MyArc.h"

namespace std {
	int main() {
		drawgrid();
		MyVector<BasePoint*> vec;
		vec.Push_back(new Line(100, 200, 200, 0, 255, 0, 255));
		vec.Push_back(new MyArc(10, 10, 5, 0, 7, 0, 255, 0));
		for (auto c : vec) {
			c->draw();
		}
		vgetchar();
		for (auto c : vec) {
			c->move(10, -10);
		}
		vgetchar();
		return 0;
	}
}
