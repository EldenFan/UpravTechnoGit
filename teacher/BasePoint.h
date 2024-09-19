#pragma once
class BasePoint {
protected:
	int x0, y0;
	int colorR, colorG, colorB;
public:
	BasePoint(int, int, int, int, int);
	virtual void draw() = 0;
	virtual void shade() = 0;
	void move(int, int);
};

