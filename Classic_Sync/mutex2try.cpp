//std::mutex::try_lock() 
//in total 9 try lock functions

//try_lock() tries to lock the mutex. Returns immediately.
//If try_lock() is not able to lock mutex, then it doesn't get blocked that's why it is called non-blocking

#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

int counter = 0;
std::mutex m;

void increaseTheCounterFor100000Time()
{
    for(int i =0; i< 100000; i++)
    {
        if(m.try_lock())
        {
            counter++;
            m.unlock();
        }
    }
}

int main()
{

    std::thread t1(increaseTheCounterFor100000Time);
    std::thread t2(increaseTheCounterFor100000Time);

    t1.join();
    t2.join();

    cout<< "Counter could increase upto :" << counter<<endl;
    return 0;

}