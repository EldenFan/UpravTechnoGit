#pragma once
#include "List.h"
class Object {
private:
	static int count;
	static List<Object*>* objectList;
protected:
	int ID;
public:
	Object();
	void virtual print();
	static void printAll();
}; 