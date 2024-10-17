#pragma once
#include "Line.h"
#include "MyArc.h"
class Segment : public Line, public MyArc, virtual public Object {
private:
	void calculateLine();
public:
    Segment(int, int, int, double, double, int = 0, int = 0, int = 0, int = 0, int = 0);
    void draw() override;
    void shade() override;
    void move(int, int);
};

