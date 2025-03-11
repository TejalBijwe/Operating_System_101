//Code for spinlock
//3 thread trying to acquire shared resource in spinloack;
//Busy-waiting //Spooling
//Atomic variable- 


#include<thread>
#include<atomic>
#include<iostream>
#include<vector>
using namespace std;

class Spinlock
{
    atomic_flag lock_flag = ATOMIC_FLAG_INIT; //Lock status

public:

    void lock()
    {
        while(lock_flag.test_and_set(memory_order_acquire));//Busy_waiting loop
    }
    void unlock()
    {
        lock_flag.clear(memory_order_release); //clear the flag,
    }
};

//Global spinlock instance
Spinlock spinlock;
int shared_counter = 0;//CS

void increment_counter(int num, int counts)
{
    for(int i =0; i< counts; i++)
    {
        spinlock.lock();//Acquire the spinlock
        shared_counter++;
        cout<< "Thread " << num << " increment counter to :"<< shared_counter<<endl;
        spinlock.unlock(); //Release
    }
}


int main ()
{
    thread t1(increment_counter,26,03);
    thread t2(increment_counter,03,05);
    thread t3(increment_counter,24,05);
    thread t4(increment_counter,02,06);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    cout<< "All Threads Finished!" <<endl;


    return 0;

}