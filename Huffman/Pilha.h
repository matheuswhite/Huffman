#ifndef PILHA_H
#define PILHA_H

    /* * * * * * * * * * * * * * * * *
    *
    * BIBLIOTECAS
    *
    * * * * * * * * * * * * * * * * */

#include <stdlib.h>
#include<QDebug>
template <typename E>

class Pilha
{
private:

    /* * * * * * * * * * * * * * * * *
    *
    * MEMBROS DA CLASSE
    *
    * * * * * * * * * * * * * * * * */

    E** cell; //Célula da pilha
    int size; //Tamanho da pilha
    int FullCapacity; //Tamanho máximo da pilha

public:

    /* * * * * * * * * * * * * * * * *
    *
    * CONSTRUTOR
    *
    * * * * * * * * * * * * * * * * */

    Pilha()
    {
        size=0;
        cell = new E*[10];
        FullCapacity=10;
    }

    /* * * * * * * * * * * * * * * * *
     *
     * MÉTODOS DA PILHA
     *
     * * * * * * * * * * * * * * * * */

    //Limpa a pilha inteira
    void clear()
    {
        delete(cell);
        cell=new E*[10];
        FullCapacity=10;
        size=0;
    }

    //Push insere um elemento no topo da pilha
    void push(E* it)
    {
        if(size < FullCapacity)
        {
            cell[size] = it;
        }
        else
        {
            cell = (E**) realloc(cell, (FullCapacity+10)*sizeof(E*) );
            cell[size] = it;
            FullCapacity += 10;
        }
        size++;
    }

    //Pop retira um elemento do topo da lista
    E* pop()
    {
        if(size!=0)
        {
            size--;
        }
        return cell[size];
    }

    //Retorna o elemento que está no topo da lista, sem retirá-lo
    E* topValue()
    {
        int i = size-1;
        return cell[i];
    }

    //Retorna o tamanho da pilha
    int length()
    {
        return size;
    }

    //Indica se a lista está vazia
    bool empty()
    {
        bool aux = false;
        if(size == 0)
        {
            aux = true;
        }
        return aux;
    }
};
#endif // PILHA_H
