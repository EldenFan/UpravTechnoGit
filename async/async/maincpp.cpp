#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <windows.h>
#define REPETER 100


volatile long long counter;
int val;
std::mutex counterMutex;
std::atomic<long long> counter2 = 0;
CRITICAL_SECTION winCS;

/*
* counterMutex.lock();
* counter += a;
* counterMutex.unlock();
* Это для fun3 и fun4
*/

/*
* counter2.fetch_add(a);
* counter2.fetch_sub(a);
* Это для fun5 и fun6
*/

/*
*EnterCriticalSection(&winCS);
* counter += a;
* LeaveCriticalSection(&winCS);		
* Это для fun7 и fun8
*/

void fun1(int a) {
	for (int i = 0; i < REPETER; i++) {
		for (int j = 0; j < 1000001; j++) {
			//Действия по + а
		}
	}
}

void fun2(int a) {
	for (int i = 0; i < REPETER; i++) {
		for (int j = 0; j < 1000000; j++) {
			//Действия по - a
		}
	}
}

void test1() {
	clock_t time0, time1;
	counter = 0;
	time0 = clock();
	fun1(val);
	fun2(val);
	time1 = clock();
	double period = ((time1 - time0) * 1000.0 / CLOCKS_PER_SEC);
} //Надо сделать, чтобы самый длинный test длился хотя бы секунду (короче подберай не меняя репитер)

void test2() {
	clock_t time0, time1;
	counter = 0;
	time0 = clock();
	std::thread th1(fun1, val);
	std::thread th2(fun2, val);
	th1.join();
	th2.join();
	time1 = clock();
	double period = ((time1 - time0) * 1000.0 / CLOCKS_PER_SEC);
}

void test3() {
	clock_t time0, time1;
	counter = 0;
	time0 = clock();
	std::thread th1(fun3, val);
	std::thread th2(fun4, val);
	th1.join();
	th2.join();
	time1 = clock();
	double period = ((time1 - time0) * 1000.0 / CLOCKS_PER_SEC);
}

void test4() {
	clock_t time0, time1;
	counter2 = 0;
	time0 = clock();
	std::thread th1(fun5, val);
	std::thread th2(fun6, val);
	th1.join();
	th2.join();
	time1 = clock();
	double period = ((time1 - time0) * 1000.0 / CLOCKS_PER_SEC);
}

void test5() {
	clock_t time0, time1;
	counter2 = 0;
	time0 = clock();
	std::thread th1(fun7, val);
	std::thread th2(fun8, val);
	th1.join();
	th2.join();
	time1 = clock();
	double period = ((time1 - time0) * 1000.0 / CLOCKS_PER_SEC);
}

int main() {
	InitializeCriticalSection(&winCS);
}

/*
* Надо реализовать также многопоточные использовать как последовательные
* Потом все прогнать через Relize и Debug в x86 и x64
*/