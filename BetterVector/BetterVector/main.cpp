#include "MyVector.h"
#include <iostream>
#include "SaturatingFloat.h"

int main()
{
	MyVector<MyVector<SaturatingFloat>> test;
	MyVector<SaturatingFloat> now;
	MyVector<SaturatingFloat> empty;

	for (double i = 0; i <= 1; i += 0.1) {
		SaturatingFloat temp = i;
		now.Push_back(temp);
	}
	test.Push_back(now);
	now = empty;
	for (double i = 1; i < 10; i++)
	{
		SaturatingFloat temp = i;
		now.Push_back(temp);
	}
	test.Push_back(now);

	for (int i = 0; i < test.GetSize(); i++)
	{
		for (int j = 0; j < test[i].GetSize(); j++) {
			test[i][j].Print();
			std::cout << "\t";
		}
		std::cout << std::endl;
	}

	for (auto a : test)
	{
		for (auto b : a) {
			 b.Print();
			 std::cout << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	test.Pop();
	test.Pop(test.begin());

	for (auto a : test)
	{
		for (auto b : a) {
			b.Print();
			std::cout << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	
	return 0;
}

