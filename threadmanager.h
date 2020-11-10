#ifndef THREADMANAGER_H_INCLUDED
#define THREADMANAGER_H_INCLUDED
#include "ThreadHandler.h"


class ThreadManager
{
    public:

    static SafeQueue<TaskBlock> blocks_queue_main;
    static void manage();
    static void fill();
    static void stop_all_threads();
};

SafeQueue<TaskBlock> ThreadManager::blocks_queue_main = SafeQueue<TaskBlock>();




void ThreadManager::manage()
{

    const auto processor_count = std::thread::hardware_concurrency();
    cout<< "processor count = " << processor_count<<endl;
    vector<ThreadHandler> arr(processor_count);


    thread main_thread(fill);//ThreadManager::fill();

    for(int i= 0; i< processor_count; i++)
    {
        //ThreadHandler h = arr[i];
        arr[i].set_source_queue(blocks_queue_main);
    }
    cout<<"joining threads";
    for(int i= 0; i< processor_count; i++)
    {
        //ThreadHandler h = arr[i];
        arr[i].initialize();
    }
    main_thread.join();
    //stop all threads at the end
    for(int i= 0; i< processor_count; i++)
    {
        //ThreadHandler h = arr[i];
        arr[i].stop();
    }
    string result = blocks_queue_main.getResult();
    if(result.length() > 0)
    {
        cout<<"result found";
    }
    else
    {
        cout<<"result not found";
    }
    cout<<"\n end of manage function";
}
 void ThreadManager::fill()
{
    unsigned int  i = 100;

    while(i-->0 && blocks_queue_main.getResult().length() ==0)
    {
        cout<<"main ThreadManager thread here"<<i<<endl;//std::stringstream s (" stream ");s<<i;//string num( i );
        char buff[245];
        std::ostringstream oss;
        oss<<i;
        TaskBlock b;
        blocks_queue_main.enqueue(b);
    }
    cout<<"filling thread end  "<<blocks_queue_main.size() <<" size = "<< &blocks_queue_main;

    while(blocks_queue_main.size() > 0 && blocks_queue_main.getResult().length() ==0) {}
    cout<<"exiting main thread now";
}

#endif // THREADMANAGER_H_INCLUDED
