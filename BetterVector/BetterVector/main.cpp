#include "MyVector.h"
#include <iostream>

int main()
{
	MyVector<int> test;

	for (int i = 0; i < 10; i++)
	{
		test.Insert(i);
	}
	for (int i = 0; i < test.GetSize(); i++)
	{
		std::cout << test[i] << "\t";
	}
	std::cout << std::endl;

	for (auto a : test)
	{
		std::cout << a << "\t";
	}
	std::cout << std::endl;

	if (std::find(test.begin(), test.end(), 1) == test.end())
	{
		std::cout << "Error" << std::endl;
	}
	else
	{
		std::cout << "Correct" << std::endl;
	}

	test.Pop();
	test.Pop(test.begin());
	test.Pop(4);

	for (auto a : test)
	{
		std::cout << a << "\t";
	}
	std::cout << std::endl;

	test.Insert(5, 4);

	for (auto a : test)
	{
		std::cout << a << "\t";
	}
	std::cout << std::endl;

	if (std::find(test.begin(), test.end(), 100) == test.end())
	{
		std::cout << "Correct" << std::endl;
	}
	else
	{
		std::cout << "Error" << std::endl;
	}


	return 0;
}

