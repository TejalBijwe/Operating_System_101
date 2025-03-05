//Qualcomm asked question
//thread1-> temp thread2->action

#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;

mutex tb;
int temperature = 25; //shared variable//Amravati temp at 8.30am 04/03/2025 

//Thread 1
void temp()
{
    for(int i =0; i<5; i++)
    {
        //tb.lock();
        lock_guard<mutex> lock(tb); //Lock acquire
        temperature +=2; //increment by 2
        cout<< "Thread 1 update Temperature: " <<temperature<< "'C"<<endl;
        this_thread::sleep_for(chrono::seconds(3)); //delay for
        //tb.unlock()
    }//automatically unlock
}
//Thread 2
void action()
{
    for(int i =0; i<5; i++)
    {
    unique_lock<mutex> lock(tb);
    cout<<"Thread 2 reads the temperature: " << temperature << "'C"<<endl;

    if(temperature<30)
    cout<< "Temperature is normal!"<<endl;
    else if(temperature>35)
    cout<< "Heat wave! Cooling system activated"<<endl;
   

    tb.unlock();
    this_thread::sleep_for(chrono::seconds(2));
    }
}

int main()
{
    thread t1(temp);
    thread t2(action);

    t1.join();
    t2.join();
    return 0;
}