#ifndef SEQUENCEGENERATOR_H_INCLUDED
#define SEQUENCEGENERATOR_H_INCLUDED
#include<string>
using namespace std;
struct CharNode;
class SequenceGenerator
{
public:
    static string s;
    static char next_char_at [256];// maximum characters in ASCII set
    static unsigned short count_chars;
    static char smallest_char;
    static char largest_char;
    static unsigned short min_length;
    static unsigned short max_length;
    static bool reached_max;

    static void fill_ASCII_range(int min_char, int max_char)
    {
        count_chars += max_char - min_char + 1;
        char min = static_cast<char> (min_char);
        char max = static_cast<char> (max_char);

        for( char c = min; c<=max-1; c++)
            next_char_at[c] = c + 1;
        if(smallest_char == 255 || largest_char == 0)
        {
            smallest_char = min;
            largest_char = max;
            next_char_at[largest_char] = smallest_char;
        }
        else{
            if(min > largest_char)
            {
                next_char_at[largest_char] = min;
                largest_char = max;
                next_char_at[max] = smallest_char;
            }
            if(max < smallest_char)
            {
                next_char_at[max] = smallest_char;
                smallest_char = min;
                next_char_at[largest_char] = smallest_char;
            }
        }
        cout<<endl<<"largest_char = " <<largest_char<<" smallest_char = "<< smallest_char;
        s=string(1, largest_char);
    }
    static string next()
    {
        int i = s.length() - 1;
        while (s[i] == largest_char && i >= 0)
            s[i--] = smallest_char;
        if (i == -1 )
        {
            if(s.length() < max_length)
                s = s + smallest_char;
            else
                reached_max = true;
        }

        else
            s[i] = next_char_at[s[i]];
        return s;
    }
    static void set_length(unsigned short u_min_length, unsigned short u_max_length)
    {
        min_length = u_min_length;
        max_length = u_max_length;
        if(min_length > 1)
        {
            string temp(1, largest_char);
            SequenceGenerator::s= string(temp);
            for(int i =0; i<min_length-2; i++)
                s = s + largest_char;
            }
    }
};
string SequenceGenerator::s = "";
char SequenceGenerator::largest_char = 0;
char SequenceGenerator::smallest_char = 255;
char SequenceGenerator::next_char_at [256]= {0};
unsigned short SequenceGenerator::count_chars = 0;
unsigned short SequenceGenerator::min_length = 0;
unsigned short SequenceGenerator::max_length = 0;
bool SequenceGenerator::reached_max = false;
#endif // SEQUENCEGENERATOR_H_INCLUDED



//
//
//static string next()
//    {
//        // If string is empty.
//    if (s == "")
//            s="a";
//
//    // Find first character from right
//    // which is not z.
//
//    int i = s.length() - 1;
//    while (s[i] == 'z' && i >= 0)
//        {
//            s[i] = 'a';
//            i--;
//        }
//    // If all characters are 'z', append
//    // an 'a' at the end.
//    if (i == -1)
//        s = s + 'a';
//
//    // If there are some non-z characters
//    else
//        s[i]++;
//
//    return s;
//    }
