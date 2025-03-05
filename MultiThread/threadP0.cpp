//CPP threading Basic
// done in after c++11 version


//#include<bits/stdc++.h>
#include<iostream>
#include<thread>
#include<chrono>
#include<algorithm>
using namespace std;
using namespace std::chrono;
typedef unsigned long long ull;

ull OddSum = 0;
ull EvenSum = 0;

void findEven(ull start, ull end)
{
    for(ull i = start; i <=end; i++)
    {
        if((i & 1) == 0)
        {
            EvenSum += i;
        }
    }
}
void findOdd(ull start, ull end)
{
    for(ull i = start; i <=end ; i++)
    {
        if((i & 1)== 1)
        {
            OddSum += i;
        }
    }
}

//Find the addition of all the odd and even numbers from 1 to 19000000000
int main()
{
 ull start = 0, end = 1900000000;
 auto startTime = high_resolution_clock::now();

 std::thread t1(findOdd, start, end); // Thread 1 with Function Pointer
 std::thread t2(findEven, start, end); // Thread 2 with Function Pointer

 t1.join(); //joining the thread1 with main thread
 t2.join(); //joining the thread2 with main thread

 //findOdd(start,end); 
 //findEven(start,end);
 
 auto stopTime = high_resolution_clock::now();
 auto duration = duration_cast<microseconds>(stopTime-startTime); //time taken

 cout<<"Odd Sum :" << OddSum << endl;
 cout<<"EvenSum :" << EvenSum << endl;

    cout<<"Sec:"<< duration.count()/1000000 << endl; //conversion microsec into sec

 return 0;
}