#ifndef BITARRAYS_H
#define BITARRAYS_H

//#define MAX = 8800
/*

definido 8192 bits
8800, pois é o menor multiplo de 8 maior que 8192
111 = (8800/8) + 1

*/

//colocar dinâmico

//setbit no final (append)
class bitArrays
{
private:
    unsigned char arraybit[111];
    unsigned char temp;
    long long int current;

public:
    bitArrays()
    {
        clear();

    }

    unsigned char* getArray()
    {
        return arraybit;
    }
    long int lenghtbit ()
    {


        return current-1;
    }

    void clear()
    {
        for(int i = 0; i < 111; i++)
        {
            arraybit[i] = 0x0000;

        }
        current =0;

        temp = 0x0000;
    }

    void setBit(unsigned int position)
    {
        if (8800 <= position)
        {
            return;         /* bit out of range */
        }


        unsigned int y = 0;
        y = (position+current)/8;



        temp = temp | (1 << ((position+current) % 8));


        arraybit[y] = temp;
        current ++;

        //cout << (int)arraybit[y] << "/" << y << endl;
    }
};

#endif // BITARRAYS_H
