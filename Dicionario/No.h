#ifndef NO_H
#define NO_H

#include <iostream>

//Comentar o codigo!!

class No
{
private:
    No* left;
    No* right;
    int frequencia;
    bool leaf;
    bool find;
    std::string code;
    unsigned char content;

public:
    No() {}

    No(unsigned char cont, int  freq, bool l, const No& esq = 0, const No& dir = 0)
    {
        code = 0;
        find = false;
        frequencia = freq;
        content = cont;
        leaf = l;
    }

    ~No() {}

    void setCode()
    {

    }
    std::string getCode()
    {

    }

    bool getFind()
    {

    }

    int getFrequencia()
    {

    }

    unsigned char getContent()
    {

    }

    bool isLeaf()
    {
        return leaf;
    }


};

#endif // NO_H
