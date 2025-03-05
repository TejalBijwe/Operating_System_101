//Mutex : Mutual Exclusive , Locking Mechanism, Protecting resources
//One thread can access critical section at a time other lock Ex : key
//Use to avoid race condition
//use lock() and unlock() on mutex

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int myAmount = 0;
std::mutex m;

void addMoney()
{ 
    m.lock();
    myAmount++;//Critical section
    m.unlock();
}
int main()
{
    std::thread t1(addMoney);//1
    std::thread t2(addMoney);//2

    t1.join();
    t2.join();

    cout<< "My balance :" << myAmount << endl;
    return 0;
}