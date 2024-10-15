#include "vstub.h"
#include "Line.h"
#include "MyArc.h"
#include "AnchorPoint.h"
#include "Sector.h"

namespace std {
	int main() {
		vc << "Hello!\n";
		drawgrid();
		Sector test(200, 200, 50, 0, 1, 0, 0, 255, 0, 255);
		test.draw();
		vgetchar();
		vc << "Fuck\n";
		test.print();
		vgetchar();
		return 0;
	}
}
