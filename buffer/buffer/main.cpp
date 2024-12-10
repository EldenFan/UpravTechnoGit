#include <iostream>
#include <thread>
#define BUFFER_SIZE 20
#define COUNT 10
using namespace std;

chrono::duration<int, std::ratio<1, 100>> wait100ms(10), wait10ms(1);

int buffer[BUFFER_SIZE];
int8_t head = 0;
int8_t tail = 0;
int res[BUFFER_SIZE * COUNT];

void fun1() {
    for (int i = 0; i < BUFFER_SIZE * COUNT; i++) {
            buffer[head] =+ i;
            head = (head + 1) % BUFFER_SIZE;
            this_thread::sleep_for(wait10ms);
    }
}

void fun2() {
    for (int i = 0; i < BUFFER_SIZE * COUNT;) {
        while (tail != head) {
            res[i] = buffer[tail];
            tail = (tail + 1) % BUFFER_SIZE;
            ++i;
        }
        this_thread::sleep_for(wait100ms);
    }
}
int main()
{
    thread th1(fun1);
    thread th2(fun2);
    cout << "Start threads\n";
    th1.join();
    th2.join();
    cout << "\nthread complete\n";
    for (int i = 0; i < BUFFER_SIZE * COUNT; i++) {
        cout << res[i] << '\n';
    }
    return 0;
}