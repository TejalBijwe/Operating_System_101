// async - usage
// 1. async - clean way to return the value from the fun.
// 2. No need to manually write join. Provides automatic thd management
//policies
//async : launch::async -> runs in a new thread (Eager running) . Will create a separate thread from main and run the function given in the arg
//async : launch::deferred -> (Lazy running)the func is not executed immediately in separate thd. Insted, it is called lazily by the main thd when .get() / .wait() is invoked.

#include<iostream>
#include<thread>
#include<future>

using namespace std;

typedef unsigned long long ull;

ull findOddSum(ull start, ull end){
    ull Oddsum = 0;
    for(ull i=start;i<=end;i++){
        if((i&1)==1){
            Oddsum += i;
        }
    }

    cout<<"Async function thread id = "<<this_thread::get_id()<<endl;
    return Oddsum;
}

int main(){

    ull start = 0;
    ull end = 1900000000;

    cout<<"Main thread function id = "<<this_thread::get_id()<<endl;
    future<ull> futureT = async(launch::deferred,findOddSum,start,end);

    cout<<"Result = "<<futureT.get()<<endl;
    return 0;
}