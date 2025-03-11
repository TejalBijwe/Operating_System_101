// Producer and Consumer Using Binary Semephore

#include<iostream>
#include<thread>
#include<semaphore>
#include<chrono>
using namespace std;

binary_semaphore producer_signal{1};
binary_semaphore consumer_signal{0};

#define buff_size 3
int buff[buff_size];

void producer()
{
    while(1)
    {
        producer_signal.acquire();
        cout<< " Produced : " <<endl;
        for(int i =0; i<buff_size; i++)
        {
            buff[i] = i*i;
            cout<< buff[i] << " " << std::flush;
            this_thread::sleep_for(chrono::seconds(2));
        }
        cout<< endl;
        consumer_signal.release();
    }
}
void consumer()
{
    while(1)
    {
        consumer_signal.acquire();
        cout<< " Consumed : " <<endl;
        for(int i =buff_size-1; i>=0; i--)
        {
            cout<< buff[i] << " "<< std::flush;
            this_thread::sleep_for(chrono::seconds(2));

        }
        cout<< endl;
        producer_signal.release();
    }
}


int main()
{
    thread producer_t(producer);
    thread consumer_t(consumer);

    cout<<" Got the signal!";
    producer_t.join();
    consumer_t.join();
    return 0;
}