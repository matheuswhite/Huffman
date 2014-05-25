#ifndef NO_H
#define NO_H

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

#endif // NO_H
