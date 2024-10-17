#include "Object.h"
#include <typeinfo>
#include "vstub.h"

int Object::count = 0;

Object::Object() {
	ID = count++;
}

void Object::print() {
	std::vc << typeid(*this).name() << ":" << ID << "\n";
}
