/*The Singleton Design Pattern ensures that a class has only one instance throughout
the program and provides a global point of access to that instance.

Key Points:
Private constructor: Prevents external instantiation.
Static instance: Holds the single object.
Public static method: Returns the instance (lazy or eager).*/



#include<iostream>
#include<mutex>
using namespace std;

class Singleton
{

private: 
    static Singleton* instance; //static pointer
    static mutex mtx;
    Singleton() {} //private constructor

public:

    static Singleton* getInstance()
    {
        if(!instance) //check if instance is null i.e not created yet
        {
            lock_guard<mutex> lock(mtx); // Lock before creating
            if(!instance) //double check
            { 
            instance = new Singleton();
            cout<< "this is done!"<<endl;
            }
        }
        return instance;
        cout<<"This is also done" << endl;
    }
};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main()
{
    Singleton* s = Singleton::getInstance();
    //s->showMessage();
    return 0;
}
