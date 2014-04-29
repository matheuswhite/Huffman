#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "byte.h"

using namespace std;


int main()
{
    long x; //Tamanho do arquivo
    long y = 0;
    FILE *input;
    ArrayByte_i array;

    //Pegar o tamanho do arquivo
    input = fopen("bola.png", "rb");
    if(input == NULL)
    {
        cout << "Nao pode ser aberto" << endl;
        return 0;
    }

    else
    {
        fseek(input, 0, SEEK_END);
        x = ftell(input);
        fseek(input, 0, SEEK_SET);
        fclose(input);
        cout << "Size: " << x << endl;
    }

    //String que receberá o conteúdo do arquivo
    char *buf;
    buf = (char*)malloc(sizeof(char)*x);

    input = fopen("bola.png", "rb");

    while(!feof(input))
    {
        y = fread(buf, 1, x, input);
        if(ferror(input))
        {
            perror("Read error");
            break;
        }
    }


    cout << buf << endl;
    cout << y << endl;



    return 0;
}
