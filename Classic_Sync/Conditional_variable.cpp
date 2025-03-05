/*
Few important points to remember while using "condition variables" are as follows:
1. Condition variables allow us to synchronise threads via notifications.
   a. notify_one();
   b. notify_all();
2. You need mutex to use condition variable
3. Condition variable is used to synchronise two or more threads.
4. Best use case of condition variable is Producer/Consumer problem.


*Condition variables can be used for two purposes:
    a. Notify other threads
    b. Wait for some condition
*/
//

#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

mutex tb;
condition_variable cv;
int balance = 0;

void addMoney(int money)
{
    lock_guard<mutex> lg(tb); //acquire the mutex
    balance+=money; //added
    cout<< "Amount added in current balance "<< balance <<endl;
    cv.notify_one();// once adding to balance it will notify to cv.wait()
    //Again the lock mutex in withdrawMoney

}

void withdrawMoney(int money)
{
    unique_lock<mutex> ul(tb); //can't withdraw when amount is less than 0 it need to unlock->relock
    cv.wait(ul, [] {return balance !=0;}); 
    //conditional_variable(lock obj, condition) 
    // if false then waiting by releasing m 
    if(balance>=money)
    {
        balance-=money; //withdrawed
        cout<< "Amount Deducted: " << money << endl;
    }
    else
    {
        cout<< "Amount can't be deducted" << money << endl;
    }
    cout<< "Current Balance: "<< balance << endl;
}


int main()
{
    thread t1(withdrawMoney,600);
    this_thread::sleep_for(chrono::seconds(2));
    thread t2(addMoney,500);

    t1.join();
    t2.join();
    return 0;
}