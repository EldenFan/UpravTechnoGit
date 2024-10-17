#include "vstub.h"
#include "Line.h"
#include "MyArc.h"
#include "AnchorPoint.h"
#include "Segment.h"

namespace std {
	int main() {
		vc << "Hello!\n";
		drawgrid();
		Segment test(200, 200, 50, 0, 1, 0, 0 , 255, 255, 0);
		MyArc test1(250, 250, 50, 0, 1, 0, 0, 255, 255, 0);
		test.draw();
		test1.draw();
		vgetchar();
		test.move(-50, -50);
		test1.move(-10, -10);
		while(true)
			vgetchar();
		return 0;
	}
}
