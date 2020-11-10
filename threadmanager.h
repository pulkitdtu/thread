#ifndef THREADMANAGER_H_INCLUDED
#define THREADMANAGER_H_INCLUDED
#include "ThreadHandler.h"
#include "sequencegenerator.h"

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
        arr[i].join();
    }

    string result = blocks_queue_main.getResult();
    if(result.length() > 0)
    {
        cout<<"result found : " << result;
    }
    else
    {
        cout<<"result not found";
    }
    cout<<"\n end of manage function";
}
 void ThreadManager::fill()
{
    SequenceGenerator::fill_ASCII_range(static_cast<int>('a'), static_cast<int>('z'));
    SequenceGenerator::fill_ASCII_range((int)'A',(int)'Z');
    SequenceGenerator::set_length(1,2);

    while(SequenceGenerator::reached_max == false && blocks_queue_main.getResult().length() ==0)
    {
        TaskBlock b;
        for(short index = 0; index < 1000; index++)
            b.push(SequenceGenerator::next(), index);
        cout<<"main ThreadManager thread here from : "<<b.arr[0] << " to : " <<b.arr[999]<<endl;//std::stringstream s (" stream ");s<<i;//string num( i );
        blocks_queue_main.enqueue(b);
    }
    cout<<"filling thread end  "<<blocks_queue_main.size() <<" size = "<< &blocks_queue_main;
    while(blocks_queue_main.size() > 0 && blocks_queue_main.getResult().length() ==0)
        {
            static size_t size = 0;
            if(size > blocks_queue_main.size())
            {
                size = blocks_queue_main.size();
            cout<< "block size =" <<blocks_queue_main.size();
            }

        }
    cout<<"exiting main thread now";
}

#endif // THREADMANAGER_H_INCLUDED
