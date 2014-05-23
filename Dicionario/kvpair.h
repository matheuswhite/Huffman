#ifndef KVPAIR_H
#define KVPAIR_H

class No
{
private:
    No* left;
    No* right;
    bool leaf;
    unsigned char content;
    int frequencia;
public:
    No(){}
    No(unsigned char cont, int  freq, bool l)
    {
        frequencia = freq; content = cont; leaf = l;
    }
};

#endif // KVPAIR_H
