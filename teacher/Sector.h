#pragma once
#include "Line.h"
#include "MyArc.h"
class Sector : public Line, public MyArc, virtual public Object {
private:
	void calculateLine();
public:
    Sector(int, int, int, double, double, int = 0, int = 0, int = 0, int = 0, int = 0);
    void draw() override;
    void shade() override;
};

