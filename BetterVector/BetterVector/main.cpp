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
	test.Push_back(now);

	for (int i = 0; i < test.GetSize(); i++)
	{
		for (int j = 0; j < test[i].GetSize(); j++) {
			test[i][j].Print();
			std::cout << "\t";
		}
		std::cout << std::endl;
	}

	std::cout << (test[0] == test[1]) << std::endl;

	for (int i = 0; i < 100; i++) {
		test.Push_back(now);
	}

	test.Rezise(8);
	for (int i = 0; i < test.GetSize(); i++) {
		for (int j = 0; j < test[i].GetSize(); j++) {
			test[i][j].Print();
			std::cout << "\t";
		}
		std::cout << std::endl;
	}

	test.Rezise(3);
	for (int i = 0; i < test.GetSize(); i++) {
		for (int j = 0; j < test[i].GetSize(); j++) {
			test[i][j].Print();
			std::cout << "\t";
		}
		std::cout << std::endl;
	}

	test.Rezise(4);

	return 0;
}

