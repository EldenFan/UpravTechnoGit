#include <thread>
#include <iostream>
#include <chrono> // для измерения времени
#define NUMBER 20000000001 // подобрать значение, чтобы выполнение заняло 5-10 сек

long long counter;
int val;

void fun1(int a, long long start, long long stop, long long* pcounter)
{
    volatile long long count = 0;
    for (long long i = start; i < stop; i++)
    {
        if (i & 1)
            count -= a;
        else
            count += a;
    }
    *pcounter = count;
}

// Измерение времени выполнения функции
template<typename Func>
void measure_time(const std::string& test_name, Func func) {
    auto start_time = std::chrono::high_resolution_clock::now();
    func();
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << test_name << " completed in " << duration.count() << " seconds.\n";
}


// test2 (int n)
void test2(int n)
{
    counter = 0;
    long long stp = 0;
    static long long Start[1000];
    static long long Stop[1000];
    static long long Res[1000];
    static std::thread* pThreads[1000];

    for (int i = 0; i < n; i++)
    {
        Start[i] = stp;
        Stop[i] = stp = stp + NUMBER / n;
        Res[i] = 0; // статический массив, поэтому лучше записывать 0
    }
    Stop[n - 1] = NUMBER;

    for (int i = 0; i < n; i++)
    {
        pThreads[i] = new std::thread(fun1, val, Start[i], Stop[i], &Res[i]);
    }
    for (int i = 0; i < n; i++)
    {
        pThreads[i]->join();
    }
    for (int i = 0; i < n; i++)
    {
        counter += Res[i];
    }
    for (int i = 0; i < n; i++)
    {
        delete pThreads[i];
    }
}

void test3(int n)
{
    counter = 0;
#pragma omp parallel for reduction(+ : counter) num_threads(n)
    for (long long i = 0; i < NUMBER; i++)
    {
        if (i < 1) counter = val;
        else counter += val;
    }
}

// main
int main(void)
{
    val = 1; // задаем значение для вычислений

    std::cout << "Starting tests...\n";

    // Измеряем время выполнения каждого теста
    measure_time("Test2 (2 threads)", []() { test2(2); });
    measure_time("Test2 (4 threads)", []() { test2(4); });
    measure_time("Test2 (8 threads)", []() { test2(8); });
    measure_time("Test2 (10 threads)", []() { test2(10); });
    measure_time("Test2 (12 threads)", []() { test2(12); });
    measure_time("Test2 (14 threads)", []() { test2(14); });
    measure_time("Test2 (16 threads)", []() { test2(16); });
    measure_time("Test2 (20 threads)", []() { test2(20); });
    measure_time("Test2 (25 threads)", []() { test2(25); });
    measure_time("Test2 (50 threads)", []() { test2(50); });
    measure_time("Test2 (100 threads)", []() { test2(100); });
    measure_time("Test2 (500 threads)", []() { test2(500); });
    measure_time("Test2 (1000 threads)", []() { test2(1000); });
    measure_time("Test3 (OpenMP with 2 threads)", []() { test3(2); });
    measure_time("Test3 (OpenMP with 4 threads)", []() { test3(4); });
    measure_time("Test3 (OpenMP with 8 threads)", []() { test3(8); });
    measure_time("Test3 (OpenMP with 10 threads)", []() { test3(10); });
    measure_time("Test3 (OpenMP with 12 threads)", []() { test3(12); });
    measure_time("Test3 (OpenMP with 14 threads)", []() { test3(14); });
    measure_time("Test3 (OpenMP with 16 threads)", []() { test3(16); });
    measure_time("Test3 (OpenMP with 20 threads)", []() { test3(20); });
    measure_time("Test3 (OpenMP with 25 threads)", []() { test3(25); });
    measure_time("Test3 (OpenMP with 50 threads)", []() { test3(50); });
    measure_time("Test3 (OpenMP with 100 threads)", []() { test3(100); });
    measure_time("Test3 (OpenMP with 500 threads)", []() { test3(500); });
    measure_time("Test3 (OpenMP with 1000 threads)", []() { test3(1000); });

    std::cout << "All tests completed.\n";

    return 0;
}
