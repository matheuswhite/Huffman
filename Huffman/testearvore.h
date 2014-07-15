#ifndef TESTARVORE_H
#define TESTARVORE_H

#include "Pilha.h"
#include "tree.h"
#include <iostream>
#include <fstream>
#include <math.h>

class TestArvore
{
public:
    TestArvore()
    {

    }

    int TestarArvore(char* pathIn, int maximo, int filenameS)
    {
        Pilha<char>* verificador = new Pilha<char>();
        int retorno;
        char* el = "(";

        std::ifstream file;

        file.open(pathIn, std::ios::binary | std::ios::in | std::ios::ate);

        int j = filenameS + 3;

        if(file.is_open())
        {
            int size = file.tellg();
            cout << "size: " << size << endl;
            file.seekg(0, std::ios::beg);

            for(int i = 0; i < j; i++)
            {
                file.get();
            }


            for(int i=0; i< maximo; i++)
            {
                unsigned char x = file.get();

                cout << x;
                if(x == '(')
                {
                    verificador->push(el);
                    //cout << endl << "foi1!" << endl;
                }
                else if(x == ')')
                {
                    verificador->pop();
                }
                if(verificador->length() == 0)
                {
                    //cout << endl << endl;
                }
            }

            if(verificador->length() != 0)
            {
                cout << "eRRo desequilibrio!" << endl;
                cout << verificador->length() << endl;
                retorno = verificador->length();
            }
            else
            {
                cout << "equilibrio" << endl;
                retorno = 0;
            }
        }
        else
        {
            cout << "eRRo TestArvore!" << endl;
            retorno = -1;
        }

        file.close();

        return retorno;
    }


    void equilibrio(int val, Tree* tree)
    {
        if(val == -1)
        {
            cout << "eRRo em cima!" << endl;
        }
        else
        {
            std::string aux;
            aux = tree->getTree_written();
            for(int i =0; i < val;i++)
            {
                aux += ')';
            }

            tree->setTree_written(aux);
        }
    }
};

#endif // TESTARVORE_H
