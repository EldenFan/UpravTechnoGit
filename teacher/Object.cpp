#include "Object.h"
#include <typeinfo>
#include "vstub.h"

int Object::count = 0;
List<Object*>* Object::objectList = new List<Object*>();

Object::Object() {
	ID = count++;
	objectList->append(this);
}

void Object::print() {
	std::vc << typeid(*this).name() << ":" << ID << "\n";
}

void Object::printAll() {
	List<Object*>* temp = objectList->head;
	while (temp)
	{
		temp->getData()->print();
		temp = temp->getNext();
	}
}
