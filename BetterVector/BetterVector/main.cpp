#include "MyVector.h"
#include <iostream>

int main()
{
	MyVector<MyVector<int>> test;
	MyVector<int> now;

	for (int i = 0; i < 10; i++)
	{
		now.Push_back(i);
	}
	test.Push_back(now);
	test.Push_back(now);
	for (int i = 0; i < test.GetSize(); i++)
	{
		for (int j = 0; j < test[i].GetSize(); j++) {
			std::cout << test[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (auto a : test)
	{
		for (auto b : a) {
			std::cout << b << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	test.Pop();
	test.Pop(test.begin());

	for (auto a : test)
	{
		for (auto b : a) {
			std::cout << b << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	return 0;
}

