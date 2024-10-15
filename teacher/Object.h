#pragma once

class Object {
private:
	static int count;
protected:
	int ID;
public:
	Object();
	void virtual print();
}; 