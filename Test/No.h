#ifndef NO_H
#define NO_H

#include <iostream>

//Comentar o codigo!!
//implementar o destrutor
class No
{
private:
    No* left;
    No* right;
    int frequencia;
    bool leaf;
    bool find;
    //std::string code;
    unsigned char content;

public:
    No();

    No(int  freq, bool l, unsigned char cont = 0)
    {
        //code.clear();
        find = false;
        frequencia = freq;
        content = cont;
        leaf = l;
        left = 0;
        right = 0;
    }

    ~No() {}

    /*
    void setCode(const std::string& codigo)
    {
        code = codigo;
    }
    std::string getCode()
    {
        return code;
    }*/


    void setFind(bool con)
    {
        find = con;
    }

    bool getFind()
    {
        return find;
    }

    int getFrequencia()
    {
        return frequencia;
    }

    unsigned char getContent()
    {
        return content;
    }

    bool isLeaf()
    {
        return leaf;
    }

    void setFilhos(No* esq, No* dir)
    {
        left = esq;
        right = dir;
    }

    No* getLeftChild()
    {
        return left;
    }

    No* getRightChild()
    {
        return right;
    }

};

#endif // NO_H
