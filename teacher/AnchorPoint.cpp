#include "AnchorPoint.h"

AnchorPoint::AnchorPoint() {
	figures = MyVector<BasePoint*>(); 
 }

AnchorPoint::AnchorPoint(const MyVector<BasePoint*>& points) {
	figures = points;
 }

void AnchorPoint::move(int dx, int dy) {
	for (auto a : figures) {
		a->move(dx, dy);
	}
}

void AnchorPoint::add(BasePoint* point) {
	figures.Push_back(point);
}

void AnchorPoint::draw() {
	for (auto a : figures) {
		a->draw();
	}
}

void AnchorPoint::shade() {
	for (auto a : figures) {
		a->shade();
	}
}
