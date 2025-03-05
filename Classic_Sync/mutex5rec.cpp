/*
std::recursive_mutex
0. It is same as mutex but, Same thread can lock one mutex multiple times using recursive_mutex.
1. If thread T1 first call lock/try_lock on recursive mutex m1, then m1 is locked by T1, now 
as T1 is running in recursion T1 can call lock/try_lock any number of times there is no issue.

2. But if T1 have acquired 10 times lock/try_lock on mutex m1 then thread T1 will have to unlock
it 10 times otherwise no other thread will be able to lock mutex m1.
It means recursive_mutex keeps count how many times it was locked so that many times it should be unlocked.

3. How many time we can lock recursive_mutex is not defined but when that number reaches and if we were calling
lock() it will return std::system_error OR if we were calling try_lock() then it will return false.*/ 


#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

//Example 1
std::recursive_mutex rm; 
int buffer = 0;

void recursion(char c, int loopFor)
{
    if(loopFor<0)
    return;

    rm.lock();
    cout<< c << " Thread ID: "<<buffer++<<endl; //cs
    recursion(c, --loopFor);
    rm.unlock();
    cout<< " Unlock by thread " <<c <<endl;
   
}

int main()
{
    thread t1(recursion, '0', 10);
    thread t2(recursion, '1', 10);
    t1.join();
    t2.join();
    return 0;
}

/*
using loops
std::recursive_mutex rm;

int main()
{
    for(int i = 0; i<5; i++)
    {
    m1.lock();
    cout<<"locked"<<i<<endl;
    }
    for(int i = 0; i<5; i++)
    {
    m1.unlock();
    cout<<"locked"<<i<<endl;
    }
    return 0;
}


*/