#include "vstub.h"
#include "Line.h"
#include "MyArc.h"
#include "AnchorPoint.h"

namespace std {
	int main() {
		drawgrid();
		MyVector<BasePoint*> a;
		int tempXStart = 0, tempYStart = 0, tempXEnd = 100, tempYEnd = 100;
		for (int i = 0; i < 5; i++) {
			tempXStart += i * 10, tempXEnd += i * 10, tempYStart += i * 10, tempYEnd += i * 10;
			Line* temp = new Line(tempXStart, tempYStart, tempXEnd, tempYEnd, 0, 0, 255, 255, 0);
			temp->draw();
			a.Push_back(temp);
		}
		MyArc* arc = new MyArc(200, 200, 50, 0, 7, 0, 0, 255, 0, 0);
		arc->draw();
		a.Push_back(arc);
		vgetchar();
		int n = a.GetSize();
		for (int i = 0; i < n; i++) {
			a[i]->shade();
		}
		vgetchar();
		AnchorPoint test(a);
		test.draw();
		vgetchar();
		test.move(10, 10);
		vgetchar();
		return 0;
	}
}
