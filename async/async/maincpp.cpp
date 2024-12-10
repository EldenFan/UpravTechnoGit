#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <windows.h>
#define REPETER 100
#define PLUS 10000001
#define MINUS 10000000


volatile long long counter;
int val;
std::mutex counterMutex;
std::atomic<long long> counter2 = 0;
CRITICAL_SECTION winCS;

void fun1(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < PLUS; j++) {
            counter += a;
        }
    }
}

void fun2(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < MINUS; j++) {
            counter -= a;
        }
    }
}

void fun3(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < PLUS; j++) {
            counterMutex.lock();
            counter += a;
            counterMutex.unlock();
        }
    }
}

void fun4(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < MINUS; j++) {
            counterMutex.lock();
            counter -= a;
            counterMutex.unlock();
        }
    }
}

void fun5(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < PLUS; j++) {
            counter2.fetch_add(a);
        }
    }
}

void fun6(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < MINUS; j++) {
            counter2.fetch_sub(a);
        }
    }
}

void fun7(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < PLUS; j++) {
            EnterCriticalSection(&winCS);
            counter += a;
            LeaveCriticalSection(&winCS);
        }
    }
}

void fun8(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < MINUS; j++) {
            EnterCriticalSection(&winCS);
            counter -= a;
            LeaveCriticalSection(&winCS);
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
    std::cout << "Sync: " << counter << "\tTime: " << period << std::endl;
}

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
    std::cout << "Async: " << counter << "\tTime: " << period << std::endl;
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
    std::cout << "Mutex async: " << counter << "\tTime: " << period << std::endl;
}

void test3_s() {
    clock_t time0, time1;
    counter = 0;
    time0 = clock();
    fun3(val);
    fun4(val);
    time1 = clock();
    double period = ((time1 - time0) * 1000.0 / CLOCKS_PER_SEC);
    std::cout << "Mutex sync: " << counter << "\tTime: " << period << std::endl;
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
    std::cout << "Atomic async: " << counter2 << "\tTime: " << period << std::endl;
}

void test4_s() {
    clock_t time0, time1;
    counter2 = 0;
    time0 = clock();
    fun5(val);
    fun6(val);
    time1 = clock();
    double period = ((time1 - time0) * 1000.0 / CLOCKS_PER_SEC);
    std::cout << "Atomic sync: " << counter2 << "\tTime: " << period << std::endl;
}

void test5() {
    clock_t time0, time1;
    counter = 0;
    time0 = clock();
    std::thread th1(fun7, val);
    std::thread th2(fun8, val);
    th1.join();
    th2.join();
    time1 = clock();
    double period = ((time1 - time0) * 1000.0 / CLOCKS_PER_SEC);
    std::cout << "Windows.h async: " << counter << "\tTime: " << period << std::endl;
}
#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <windows.h>
#define REPETER 100
#define PLUS 10000001
#define MINUS 10000000


volatile long long counter;
int val;
std::mutex counterMutex;
std::atomic<long long> counter2 = 0;
CRITICAL_SECTION winCS;

void fun1(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < PLUS; j++) {
            counter += a;
        }
    }
}

void fun2(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < MINUS; j++) {
            counter -= a;
        }
    }
}

void fun3(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < PLUS; j++) {
            counterMutex.lock();
            counter += a;
            counterMutex.unlock();
        }
    }
}

void fun4(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < MINUS; j++) {
            counterMutex.lock();
            counter -= a;
            counterMutex.unlock();
        }
    }
}

void fun5(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < PLUS; j++) {
            counter2.fetch_add(a);
        }
    }
}

void fun6(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < MINUS; j++) {
            counter2.fetch_sub(a);
        }
    }
}

void fun7(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < PLUS; j++) {
            EnterCriticalSection(&winCS);
            counter += a;
            LeaveCriticalSection(&winCS);
        }
    }
}

void fun8(int a) {
    for (int i = 0; i < REPETER; i++) {
        for (int j = 0; j < MINUS; j++) {
            EnterCriticalSection(&winCS);
            counter -= a;
            LeaveCriticalSection(&winCS);
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
    std::cout << "Sync: " << counter << "\tTime: " << period << std::endl;
} 

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
    std::cout << "Async: " << counter << "\tTime: " << period << std::endl;
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
    std::cout << "Mutex async: " << counter << "\tTime: " << period << std::endl;
}

void test3_s() {
    clock_t time0, time1;
    counter = 0;
    time0 = clock();
    fun3(val);
    fun4(val);
    time1 = clock();
    double period = ((time1 - time0) * 1000.0 / CLOCKS_PER_SEC);
    std::cout << "Mutex sync: " << counter << "\tTime: " << period << std::endl;
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
    std::cout << "Atomic async: " << counter2 << "\tTime: " << period << std::endl;
}

void test4_s() {
    clock_t time0, time1;
    counter2 = 0;
    time0 = clock();
    fun5(val);
    fun6(val);
    time1 = clock();
    double period = ((time1 - time0) * 1000.0 / CLOCKS_PER_SEC);
    std::cout << "Atomic sync: " << counter2 << "\tTime: " << period << std::endl;
}

void test5() {
    clock_t time0, time1;
    counter = 0;
    time0 = clock();
    std::thread th1(fun7, val);
    std::thread th2(fun8, val);
    th1.join();
    th2.join();
    time1 = clock();
    double period = ((time1 - time0) * 1000.0 / CLOCKS_PER_SEC);
    std::cout << "Windows.h async: " << counter << "\tTime: " << period << std::endl;
}


void test5_s() {
    clock_t time0, time1;
    counter = 0;
    time0 = clock();
    fun7(val);
    fun8(val);
    time1 = clock();
    double period = ((time1 - time0) * 1000.0 / CLOCKS_PER_SEC);
    std::cout << "Windows.h sync: " << counter << "\tTime: " << period << std::endl;
}


int main() {
    InitializeCriticalSection(&winCS);
    std::cin >> val;
    test1();
    test2();
    test3();
    test3_s();
    test4();
    test4_s();
    test5();
    test5_s();
    return 0;
}
