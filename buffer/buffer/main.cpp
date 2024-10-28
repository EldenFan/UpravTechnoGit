#include <iostream>
#include <thread>
#define BUFFER_SIZE 20
using namespace std;

chrono::duration<int, std::ratio<1, 100>> wait100ms(10), wait10ms(1);

int buffer[BUFFER_SIZE];
int head = 0;
int tail = 0;
int c = 0;
int res[BUFFER_SIZE * 10];

void fun1() {
    for (int i = 0; i < BUFFER_SIZE * 10; i++) {
        if (c == BUFFER_SIZE) {
            --i;
            this_thread::sleep_for(wait100ms);
        }
        else {
            cout << "Read" << endl;
            buffer[head] = i;
            head = (head + 1) % BUFFER_SIZE;
            ++c;
            this_thread::sleep_for(wait10ms);
        }
    }
}

void fun2() {
    for (int i = 0; i < BUFFER_SIZE * 10; i++) {
        if (c == 0) {
            --i;
            this_thread::sleep_for(wait10ms);
        }
        else {
            cout << "Write" << endl;
            res[i] = buffer[tail];
            tail = (tail + 1) % BUFFER_SIZE;
            --c;
            this_thread::sleep_for(wait100ms);
        }
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
    for (int i = 0; i < BUFFER_SIZE * 10; i++) {
        cout << res[i] << '\t';
    }
    return 0;
}