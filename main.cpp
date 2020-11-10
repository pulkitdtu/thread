#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <string.h>
#include <strings.h>
#include <cstring>
#include <strstream>
#include <sstream>
#include "threadmanager.h"

using namespace std;

std::mutex mutexGlobal;
queue<string> q;

struct TaskBlock;
class ThreadHandler;

bool stop = false;

void function1()
{
    unsigned int  i = 10000;
    while(!stop)
    {
        string s ="";
        {
            std::lock_guard<mutex> guard(mutexGlobal);
            if(!q.empty())
            {
                s = q.front();
                q.pop();
            }
        }
        if(s.length()>2)
        {//std::lock_guard<mutex> guard(mutexGlobal);
            cout<<endl<<this_thread::get_id()<<" id  thread executing :"<<i<<"  "<<s<<endl;
        }
        else
        {
            i--;
        }
    }
    cout<<endl<<this_thread::get_id()<<" id  thread exiting \n";

}


 void function_main()
{
unsigned short  i = 10000;

    while(i-->0)
    {
        std::lock_guard<std::mutex> guard(mutexGlobal);
        cout<<"main thread here"<<i<<endl;//std::stringstream s (" stream ");s<<i;
        //string num( i );

        char buff[245];
        std::ostringstream oss;
        oss<<i;
        q.push("main = " + oss.str());
    }
    stop = true;
    }
int main()
{
    cout << "Hello world!" << endl;
    cout << "Hello world again" << endl;//char a;
    //thread t_main(function_main);
    //thread t(function1);
    //thread t2(function1);
    //thread t3(function1);
    //thread t4(function1);
    const auto processor_count = std::thread::hardware_concurrency();
    cout<< "processor count = " << processor_count<<endl;

    cout<<"\n joining threads \n";
    //t_main.join();
    //t.join();
    //t2.join();
    //t3.join();
    //t4.join();//t1.join();
    ThreadManager::manage();
    string s;
    cin>>s;

    cin>>s;
    cout<< "string entered : "<<s;
    return 0;
}





