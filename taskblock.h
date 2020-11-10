#ifndef TASKBLOCK_H_INCLUDED
#define TASKBLOCK_H_INCLUDED
#include<string>
#include "md5.h"
using namespace std;
struct TaskBlock
{
    std::array<string, 10000> arr;
    string process(const string& hash);
    void fill();
    bool empty(){return arr.empty();}
};

string TaskBlock::process(const string& hash)
{
    cout<<" \t process called \n";
     static MD5 algo;
    for(const string& s :arr)
    {
    string digest = string(algo.digestString(const_cast<char*> (s.c_str())));
    if(hash == digest)
        return s;
    }
    // nothing found
    return "";
}

#endif // TASKBLOCK_H_INCLUDED
