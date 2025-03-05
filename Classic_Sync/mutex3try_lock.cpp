//Multiple mutex one try lock 
//std::try_lock(m1,m2,m3,m4....mn)



#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;

int X = 0, Y= 0;
std::mutex m1,m2;

void doSomeWorkForSeconds(int seconds) {std::this_thread::sleep_for(std::chrono::seconds(seconds));}

void produceXY(int& XorY, std::mutex& m, const char* desc)
{
    for(int i=0; i<5; i++)
    {
        m.lock();
            XorY++;
            cout<< desc << XorY <<'\n';
        m.unlock();
        doSomeWorkForSeconds(2);
    }
}
void consumerXY()
{
    int useCount =5;
    int XplusY = 0;
    while(2)
    {
        int lockResult = std::try_lock(m1,m2);
        if(lockResult == -1)
        {
            if(X!=0 && Y!=0)
            {
                useCount--;
                XplusY += X+Y;
                X=0;
                Y=0;
                cout<< "XplusY" << XplusY <<'\n';
            }
            m1.unlock();
            m2.unlock();
            if(useCount == 0) break;
        }
    }
}

int main()
{
    std::thread t1(produceXY, std::ref(X), std::ref(m1), "X ");
    std::thread t2(produceXY, std::ref(X), std::ref(m2), "Y ");
    std::thread t3(consumerXY);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}
