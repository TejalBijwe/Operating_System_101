/*
(std::lock_guard<mutex> lock(m1))

Few points to remember about the lock_guard is as follows:
0. It is very light weight wrapper for owning mutex on scoped basis.
1. It acquires mutex lock the moment you create the object of lock_guard.-> 
2. It automatically removes the lock while goes out of scope.
3. You can not explicitly unlock the lock_guard.
4. You can not copy lock_guard.

flow-> creat a object of lockguard which contains the lock for a thread2->thread 1 execute. scope over for the object of thread 2 lock over
-> destructor call for unlocking thread 2-> and then implement cs for thread 2
kind of automatic behavior
*/
#include<iostream>
#include<thread>
#include<mutex>
using namespace std;


std::mutex m1;
int buffer = 0;
void task(const char* threadNumber, int loopFor)
{
    //m1.lock();
    std::lock_guard<mutex>lock(m1);
    for(int i =0; i< loopFor; i++)
    {
        buffer++;
        cout<<"Thread Number " <<threadNumber <<buffer <<endl;
    }
    //m1.unlock();
}

 
int main()
{
    thread t1(task, "T1:", 10);
    thread t2(task, "T2:", 10);
    t1.join();
    t2.join();
    return 0;
}