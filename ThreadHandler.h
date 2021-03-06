#ifndef THREADHANDLER_H_INCLUDED
#define THREADHANDLER_H_INCLUDED
#include "taskblock.h"
#include "safequeue.h"
using namespace std;
class ThreadHandler
{//deque source;
    //deque<string> source;
    SafeQueue<TaskBlock> source_queue;//shared object needs mutex;
    bool stop_flag;
    thread* thread1;
    //source
    public:
    ThreadHandler():stop_flag(false), source_queue(){}
    ~ThreadHandler(){delete thread1;}
    void process_task_block();
    void fillQueue();
    void join();
    void set_source_queue(SafeQueue<TaskBlock>& q);
    void set_mutex(std::mutex* l);
    void stop();
    void initialize();
};

void ThreadHandler::process_task_block()
{
    string hash1 = source_queue.getHash();
    while(!stop_flag)
    {
        {// locked area of the code

                TaskBlock block = source_queue.dequeue();
                cout<<"\n entered block";
                //if(!block.empty())
                //std::lock_guard<mutex> guard(mutexGlobal);
                    cout<<endl<<this_thread::get_id()<<" id  thread executing : "<< block.arr[0] <<" to " <<block.arr[999] <<endl;
                    //process block
                    string s = block.process(hash1);
                    if(s.length()>0)
                        source_queue.setResult(s);
        }

    }
    cout<<endl<<this_thread::get_id()<<" id  thread exiting \n";
}


void ThreadHandler::stop()
{
    stop_flag = true;

}
class a {};
void b(a a1)
{

    a a3 = a1;
}
void ThreadHandler::set_source_queue(SafeQueue<TaskBlock>& q)
{
    source_queue = q;
    cout<< "source queue size and address " <<source_queue.size() << " address = " <<&source_queue;
}

void ThreadHandler::join()
{
    if(thread1->joinable())
        thread1->join();
}

void ThreadHandler::initialize()
{
    thread1 = new thread ( &ThreadHandler::process_task_block, this);
}
#endif // THREADHANDLER_H_INCLUDED
