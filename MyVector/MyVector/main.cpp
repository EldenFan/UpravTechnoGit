#include<iostream>
#include "MyVector.h"

int main()
{
	MyVector<int> test;

	for (int i = 0; i < 10; i++)
	{
		test.PushBack(i);
	}

	for (int i = 0; i < test.GetSize(); i++)
	{
		std::cout << test[i] << "\t";
	}
	std::cout << std::endl;

	MyVector<int> test2;

	for (int i = 9; i > -1; i--)
	{
		test2.PushBack(i);
	}

	MyVector<int> test3(test);

	test = test2;

	for (int i = 0; i < test.GetSize(); i++)
	{
		std::cout << test[i] << "\t";
	}
	std::cout << std::endl;

	for (int i = 0; i < test3.GetSize(); i++)
	{
		std::cout << test3[i] << "\t";
	}
	std::cout << std::endl;

	test3.Pop(2);

	for (int i = 0; i < test3.GetSize(); i++)
	{
		std::cout << test3[i] << "\t";
	}
	std::cout << std::endl;

	return 0;
}