#pragma once
#include "MyVector.h"
#include "BasePoint.h"
class AnchorPoint
{
private:
	MyVector<BasePoint*> figures;
public:
	AnchorPoint();
	AnchorPoint(const MyVector<BasePoint*>&);
	void add(BasePoint*);
	void move(int dx, int dy);
	void draw();
	void shade();
};

