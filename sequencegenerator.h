#ifndef SEQUENCEGENERATOR_H_INCLUDED
#define SEQUENCEGENERATOR_H_INCLUDED

class SequenceGenerator
{
public:
    static string s;
    static string next()
    {
        // If string is empty.
    if (s == "")
        return "a";

    // Find first character from right
    // which is not z.

    int i = s.length() - 1;
    while (s[i] == 'z' && i >= 0)
        i--;

    // If all characters are 'z', append
    // an 'a' at the end.
    if (i == -1)
        s = s + 'a';

    // If there are some non-z characters
    else
        s[i]++;

    return s;
    }
};
string SequenceGenerator::s = "";
#endif // SEQUENCEGENERATOR_H_INCLUDED
