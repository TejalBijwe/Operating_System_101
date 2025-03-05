/*
Producer Consumer OR Bounded Buffer Problem Using MUTEX and condition_variable

THE PROBLEM STATEMENT:
 1. Producer will produce and consumer will consume with synchronisation of a common buffer.
 2. Until producer thread produces any data consumer thread can't consume.
 3. Threads will use condition_variable to notify each other.
 4. We need mutex if we use condition_variable because CV waits on mutex.
 5. This is one of the example of producer consumer there are many.

PRODUCER thread steps:
 1. lock mutex, if success then go ahead otherwise wait for mutex to get free.
 2. check if buffer is full and if it is full then unlock mutex and sleep, if not then go ahead and produce.
 3. insert item in buffer.
 4. unlock mutex. 
 5. notify consumer.

CONSUMER thread steps:
 1. lock mutex, if success then go ahead otherwise wait for mutex to get free.
 2. check if buffer is empty and if it is, then unlock the mutex and sleep, if not then go ahead and consume.
 3. consume item from buffer.
 4. unlock mutex.
 5. notify producer.

*/
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<deque>
using namespace std;

mutex pc;
condition_variable cv;
deque<int> buffer; //CS
const unsigned int maxBufferSize = 2;

void producer(int value)
{
    while(value)
    {
        unique_lock<mutex> lock(pc);
        cv.wait(lock, []{return buffer.size() < maxBufferSize;});
        buffer.push_back(value);
        cout<< "Produced Value: "<<value<<endl;
        value--;
        lock.unlock();
        cv.notify_one();
    }
}
void consumer()
{
    while(true)
    {
        unique_lock<mutex> lock(pc);
        cv.wait(lock, [] {return buffer.size() > 0;});
        int value=buffer.back();
        buffer.pop_back();
        cout<< "Consumed Value: "<<value<<endl;
        lock.unlock();
        cv.notify_one();
    }
}
int main()
{
    thread t1(producer,10);
    thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}