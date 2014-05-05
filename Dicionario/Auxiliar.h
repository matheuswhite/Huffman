#ifndef AUXILIAR_H
#define AUXILIAR_H

#include <iostream>

using namespace std;

void Assert(bool condition, string str)
{
    if(condition == false)
    {
        cout << str << endl;
    }
}

int freq(char elem, char* str,int size)
{
    int j=0;

    for(int i = 0;i<size;++i)
    {
        if(elem == str[i])
        {
            j++;
        }
    }

    return j;
}

int sizeStr(char* str)
{
    int i=0;
    while(str[i] != '\0')
    {
        ++i;
    }
    return i-1;
}

#endif // AUXILIAR_H
