// promise - Setter//Set the value//used to send the value to the worker thread and set the values in worker thread.
// future - Getter//retrive it//used to get the values from the promise, wait for the promise / will get blocked until promise set the value in worker and returns it to the future.get().


#include<iostream>
#include<thread>
#include<chrono>
#include<algorithm>
#include<future>
using namespace std;

typedef  unsigned long long ull;

void findOddSum(promise<ull>&& Oddpromise,ull start, ull end){
    ull OddSum = 0;

    for(ull i=start;i<=end;i++){
        if((i&1)==1){
            OddSum+=i;
        }
    }
    Oddpromise.set_value(OddSum);
}

int main(){

    ull start = 0;
    ull end = 190000000;

    promise<ull> OddSum;
    future<ull> Oddfuture = OddSum.get_future();

    thread t1(findOddSum,move(OddSum),start,end);

    cout<<"Waiting for the future"<<endl;

    cout<<"Odd Sum = "<<Oddfuture.get()<<endl;
    this_thread::sleep_for(chrono::seconds(5));
    t1.join();

    return 0;
}