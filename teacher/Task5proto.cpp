#include "vstub.h"
#include "Line.h"
#include "MyArc.h"
#include "AnchorPoint.h"
#include "Segment.h"
#include "Sector.h"

namespace std {
	int main() {
		vc << "Hello!\n";
		drawgrid();
		Segment test(200, 200, 50, 0, 1, 0, 0 , 255, 255, 0);
		Sector test1(300, 100, 50, 0, 3.14 / 2, 0, 0, 255, 0, 0);
		test.draw();
		test1.draw();
		vgetchar();
		test.move(-50, -50);
		test1.move(20, 20);
		while(true)
			vgetchar();
		return 0;
	}
}
