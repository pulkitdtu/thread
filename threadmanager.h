#ifndef THREADMANAGER_H_INCLUDED
#define THREADMANAGER_H_INCLUDED
#include "ThreadHandler.h"
#include "sequencegenerator.h"
#include <algorithm>    // std::find_if
#include <string>

class ThreadManager
{
    public:

    static SafeQueue<TaskBlock> blocks_queue_main;
    static void manage();
    static void fill();
    static void stop_all_threads();
    static void command_line(int arc, char* argv[]);
};

SafeQueue<TaskBlock> ThreadManager::blocks_queue_main = SafeQueue<TaskBlock>();
bool is_number(string s);



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
    //SequenceGenerator::fill_ASCII_range(static_cast<int>('a'), static_cast<int>('z'));
    //SequenceGenerator::fill_ASCII_range((int)'A',(int)'Z');
    //SequenceGenerator::set_length(1,3);

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

void ThreadManager::command_line(int argc, char* argv[])
{
    bool is_filled = false;
    short min_length =-1, max_length =-1;
    for(unsigned short i= 0; i<argc; i++)
    {
        string s = argv[i];
        cout<<s<< ":\n";
        if(s.find('-') != std::string::npos)
        {
            size_t pos = 0;
            std::vector<string> strings;
           if(s.find(':') != std::string::npos)
           {
                string s2 = string(s);
                while ((pos = s2.find(":")) != std::string::npos) {
                    strings.push_back(s2.substr(0, pos));
                    s2.erase(0, pos + 1);
                }
                strings.push_back(s2);
           }
           else
                strings.push_back(s);
            string s2 = string(s);
            for(string s1 : strings)
            {
                if((pos = s1.find("-")) != std::string::npos)
                {
                    string min_char_code = s1.substr(0, pos);
                    s1.erase(0, pos + 1);
                    string max_char_code = s1;
                    if(is_number(min_char_code) && is_number(max_char_code))
                    {
                        int min_char = atoi(min_char_code.c_str());
                        int max_char = atoi(max_char_code.c_str());
                        SequenceGenerator::fill_ASCII_range(min_char, max_char);
                        is_filled = true;
                    }
                }
            }
        }

        else if(s.length() == 32)
        {
            blocks_queue_main.setHash(s);
        }
        else
        {
            if(is_number(s))
            {
                unsigned int length = atoi(s.c_str());
                if(min_length <0)
                    min_length = length;
                else if(max_length < 0)
                    max_length = length;
            }
        }
    }
    if(!is_filled)
    {
        SequenceGenerator::fill_ASCII_range(static_cast<int>('a'), static_cast<int>('z'));
        SequenceGenerator::fill_ASCII_range((int)'A',(int)'Z');
    }
    if(min_length <0 || max_length < 0)
    {
        min_length = 1;
        max_length = 3;
    }
    SequenceGenerator::set_length(min_length, max_length);

}

bool is_number(string s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
#endif // THREADMANAGER_H_INCLUDED
