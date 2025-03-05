/*
1. The class unique_lock is a mutex ownership wrapper.->own the mutex
2. It Allows:
    a. Can Have Different Locking Strategies
    b. time-constrained attempts at locking (try_lock_for, try_lock_until)
    c. recursive locking
    d. transfer of lock ownership (move not copy)
    e. condition variables. 

    std::uniqie_lock<mutex> lock(m1);
                             obj
Locking Strategies -> obj(m1,Locking Strategies)
   TYPE           EFFECTS(S)
1. defer_lock  do not acquire ownership of the mutex.(wrap the mutex but not lock it , locking happenes afterwards)
2. try_to_lock  try to acquire ownership of the mutex without blocking.
3. adopt_lock  assume the calling thread already has ownership of the mutex.

lock->do some work-> temporary unlock-> do some other work-> relock-> lock will automaically unlock when out of scope

*/

#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

std::mutex m1;
int buffer = 0;
//Ex:1

// void task(const char* threadNumber, int loopFor)
// {
//     std::unique_lock<mutex> lock(m1); //Uniqie lock-> automatically calls lock on mutex m1
//     for(int i =0; i< loopFor; i++)
//     {
//         buffer++;
//         cout<<"Thread Number " <<threadNumber <<buffer <<endl;
//     }
// }

//Ex:2

void task(const char* threadNumber, int loopFor)
{
    std::unique_lock<mutex> lock(m1, std::defer_lock); //Defer lock :wrap the mutex but not lock it , locking happenes afterwards
    lock.lock();//Lock it explicitly because of defer_lock
    for(int i =0; i< loopFor; i++)
    {
        buffer++;
        cout<<"Thread Number " <<threadNumber <<buffer <<endl;
    }
    //lock.unlock(); // is not nedded as unlocking is done by destructor of unique_lock
}

int main()
{
    thread t1(task, "T1:", 10);
    thread t2(task, "T2:", 10);
    t1.join();
    t2.join();
    return 0;
}