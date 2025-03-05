// Join -Once the thread is started we call join() to create and run the thread
    //double joining will resulting in program termination
//Joianble -if nedded we should check thread is joinable or not by joinable()
//Deteched
    //This is used to creat newly created thread from the parent thread.
        //single threaded program has main as its parent
    //always check if thread is joinable before detaching



#include<iostream>
#include<chrono>
#include<thread>

using namespace std;

void run(int count)
{
    while(count --> 0){
    cout << count << " Me VS Me "<<endl;
    //std::this_thread::sleep_for(chrono::seconds(2));
    cout<< "Tejal" << endl;
    }
}
int main()
{
    std::thread t(run, 5);
    cout<< "main()"<<endl;


    t.detach();
    //t.join();

    //after 1000 lines of code if we want to check thread is joinable or not
    // if(t.joinable())
    // t.join();
    cout<< "main()after"<<endl; //Wait for 3 seconds
    std::this_thread::sleep_for(chrono::seconds(2));
    return 0;
}