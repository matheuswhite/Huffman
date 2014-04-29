#ifndef BYTE_H
#define BYTE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef unsigned char* byte_c;
typedef unsigned char** ArrayByte_c;

typedef unsigned long int byte_i;
typedef unsigned long int* ArrayByte_i;
typedef unsigned short int bit_i;




//Transformar um char em 1 Byte(int)
//Falta Implementar
byte_i readCharToByte_i(char c);
//transformar 8 bits em 1 byte
//Pronto!
byte_i bit_8ToByte(bit_i* bit)
{
    byte_i bytes = 0;
    for(int i=1;i<100000000;i*=10)//1 10 100 1000 10000 100000 1000000 10000000
    {
        bytes += bit[i] * i;
    }

    return bytes;
}
//Transformar uma string em um Array de Bytes(int)
//Pronto!
ArrayByte_i readStringToArrayByte_i(char* s, int size)
{
    bit_i *byte_array;
    bit_i b[8];
    byte_i* bytes;
    bit_i **other;
    int x;

    int i=0;
    int h=0;

    bytes = new byte_i[size];

    byte_array = new bit_i[size];

    other = new bit_i*[size];
    for(int i=0; i < size; ++i)
    {
        other[i] = new bit_i[8];
    }


    while(s[i])
    {
        x = s[i]; // converts a char to its int form
        for(int j=0;j<8;++j)
        { // b[] stors the binary form of x but backwords
            b[j]=x%2;
            x=x/2;
        }

        for(int j=7;j>-1;--j)
        {
            byte_array[h]=b[j]; //adds b to byte_array[] but in the right way
            ++h;
        }

        ++i;
    }
    //Array em bits e bagunçado

    //Dividir o Array em uma Matiz de bits
    for(int i=0; i < size/8; ++i)
    {
        for(int j=0; j< 8; ++j)
        {
            other[i][j] = byte_array[i+j];
        }
    }

    //Transformar cada Array da Matriz de bits em 1 Byte
    for(int i=0; i< (size/8); ++i)
    {
        bytes[i] = bit_8ToByte(other[i]);
    }

    delete[] other;
    delete[] byte_array;

    return bytes;
}
//Transformar um char em 1 Byte(string)
//Falta Implementar
byte_c readCharToByte_c(char c);
//Transformar uma string em um Array de Bytes(string)
//Falta Implementar
ArrayByte_c readStringToArrayByte_c(char* s, int size);




//Retorna o tamanho do arquivo
//Falta Implementar
int sizeFile(char* path, char* mode);

//Retorna o conteudo do arquivo em um array de Bytes(string)
/*
 * lê o arquivo;
 * salva o conteudo numa string;
 * tranforma aquela string num Array de Bytes(string)
 *
 */
//Falta Implementar
ArrayByte_c readContentFile_c(char* path, int size);

//Retorna o conteudo do arquivo em um array de Bytes(int)
//Falta Implementar
ArrayByte_i readContentFile(char *path, int size);

//Escreve o conteudo desejado num arquivo
//Falta Implementar
void writeContentFile(char *path, char* content);




#endif // BYTE_H
