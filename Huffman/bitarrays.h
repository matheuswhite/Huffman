#ifndef BITARRAYS_H
#define BITARRAYS_H

    /* * * * * * * * * * * * * * * * *
    *
    * BIBLIOTECAS
    *
    * * * * * * * * * * * * * * * * */


#include <iostream>

class bitArrays
{
private:

    /* * * * * * * * * * * * * * * * *
    *
    * MEMBROS DA CLASSE
    *
    * * * * * * * * * * * * * * * * */


    unsigned char arraybit[1110];
    unsigned char temp;
    long long int current;
    long long int c;

public:

    /* * * * * * * * * * * * * * * * *
    *
    * CONSTRUTOR
    *
    * * * * * * * * * * * * * * * * */

    bitArrays()
    {
        clear();
        current = 0;
    }

    /* * * * * * * * * * * * * * * * *
    *
    * MÉTODOS DO BITARRAY
    *
    * * * * * * * * * * * * * * * * */

    //Recebe o bitarray
    unsigned char* getArray()
    {
        return arraybit;
    }

    //Retorna o tamanho do lixo
    short int trashLenght()
    {
        //cout << endl << current << endl;
        return 8 - (current % 8);
    }
    //Retorna o tamanho do bitarray
    long int lenghtbit ()
    {
        return current;
    }

    //"Seta" o valor do apontador
    void setCurrent()
    {
        current++;
    }

    //Recebe o valor do apontador
    long long int getCurrent()
    {
        return current;
    }
    //Método para limpar totalmente o bitarray
    void clear()
    {
        for(int i = 0; i < 111; i++)
        {
            arraybit[i] = 0x0000;

        }
        current = 0;

        temp = 0x0000;
    }

    //Recebe uma string com 8 elementos
    void setBit(std::string eight)
    {
        std::string aux;
        unsigned int y = 0;

        //y será a posição do array
        y = (current)/8;

        //irá setar 8 bit's
        for(int i = 0; i < 8; i++)
        {
            aux = eight.substr(i, 1);
            if(aux == "1")
            {
                temp = temp | (1 << (i % 8));
            }
            arraybit[y] = temp;
            current ++;
        }
        //limpa o temp
        temp = 0x0000;
    }

    //"Seta" um bit no bitarray
    void setBit(std::string eight, int size)
    {
        std::string aux;
        unsigned int y = 0;

        //cout << size << endl;

        //y será a posição do array
        y = (current)/8;

        //irá setar 8 bit's
        for(int i = 0; i < size; i++)
        {
            aux = eight.substr(i, 1);
            if(aux == "1")
            {
                temp = temp | (1 << i);
            }
            arraybit[y] = temp;
            current ++;
        }

        c = current;

        //limpa o temp
        temp = 0x0000;
    }
};

#endif // BITARRAYS_H
