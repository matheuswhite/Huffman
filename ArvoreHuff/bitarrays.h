#ifndef BITARRAYS_H
#define BITARRAYS_H

//#define MAX = 104
/*

definido 100 bits
104, pois é o menor multiplo de 8 maior que 100
14 = (104/8) + 1

*/

//colocar dinâmico
class bitArrays
{
private:
    unsigned char arraybit[14];
    unsigned char temp;

public:
    bitArrays()
    {
        clear();
        temp = 0x0000;
    }

    unsigned char* getArray()
    {
        return arraybit;
    }

    void clear()
    {
        for(int i = 0; i < 14; i++)
        {
            arraybit[i] = 0x0000;
        }
    }
    void setBit(unsigned int position)
    {
        if (104 <= position)
        {
            return;         /* bit out of range */
        }


        unsigned int y = 0;
        y = position/8;



        temp = temp | (1 << (position % 8));


        arraybit[y] = temp;

        //cout << (int)arraybit[y] << "/" << y << endl;
    }
};

#endif // BITARRAYS_H
