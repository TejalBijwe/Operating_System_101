//Creating threads in c++11
//there are 5 ways 
//NOTE: if multiple threads are created a time it doesn't guarantee which one will start first

#include<bits/stdc++.h>
using namespace std;

//1: Function pointer
// void fun(int x)
// {
//     while(x --> 0)
//     {
//         cout<< x <<endl;
//     }
// }
// int main ()
// {
//  std::thread t1(fun, 11);
//  //std::thread t2(fun, 10);
//  t1.join();
//  //t2.join();
//  return 0;
// }

// //2: Lambda Function
// int main()
// {
//     //auto fun = 
//    //We can directly injext lambda at thread creationg time.
//     std::thread t([](int x)
//     {
//         while(x --> 0)
//         {
//             cout<< x << endl; 
//         }
//     },10);
//     t.join();
//     return 0;
// }

//3. Functor(Function Object)
// class Base
// {
// public: 
//     void operator()(int x)
//     {
//         while(x --> 0)
//         {
//             cout<< x << endl;
//         }
//     }
// };

// int main()
// {
//     std::thread t((Base()),10);
//     t.join();
//     return 0;
// }
//4. Non-static Function
// class Base
// {
// public:
//     void run(int x)
//     {
//         while(x --> 0)
//         {
//             cout<< x << endl;
//         }
//     }
// };
// int main()
// {
//     Base b;
//     std::thread t(&Base::run, &b, 10); //run is inside base class, and passing the object
//     t.join();
//     return 0;
// }
//5. Static Function
class Base
{
public:
    static void run(int x)
    {
        while(x --> 0)
        {
            cout<< x << endl;
        }
    }
};
int main()
{
    Base b;
    std::thread t(&Base::run, 10); //run is inside base class, and not passing the object
    t.join();
    return 0;
}