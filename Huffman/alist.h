#ifndef ALIST_H
#define ALIST_H

    /* * * * * * * * * * * * * * * * *
    *
    * BIBLIOTECAS
    *
    * * * * * * * * * * * * * * * * */


#include <iostream>
#include <QList>
#include "No.h"
using namespace std;


//Lista baseada em Array
class AList {
private:


    /* * * * * * * * * * * * * * * * *
    *
    * MEMBROS DA CLASSE
    *
    * * * * * * * * * * * * * * * * */

    int maxSize; // Tamanho máximo da lista
    int listSize; // Número de items na lista no momento
    int curr; // Posição do elemento corrente
    No** listArray; // Array que contem os elementos da lista

public:

    /* * * * * * * * * * * * * * * * *
     *
     * CONSTRUTOR
     *
     * * * * * * * * * * * * * * * * */


    AList(int size=0) {
        maxSize = 256;
        listSize = curr = 0;
        listArray = new No*[maxSize];
    }


     /* * * * * * * * * * * * * * * * *
     *
     * DESTRUTOR
     *
     * * * * * * * * * * * * * * * * */


    ~AList()
    {
        delete [] listArray;
    }


    /* * * * * * * * * * * * * * * * *
     *
     * MÉTODOS DA LISTA
     *
     * * * * * * * * * * * * * * * * */

    //
    int Assert(bool condition, std::string name)
    {
        if(condition == false)
        {
            return -71;
        }
    }

    //Método para limpar a lista totaltmente
    void clear() { // Reinitialize the list
        delete [] listArray; // Remove the array
        listSize = curr = 0; // Reset the size
        listArray = new No*[maxSize]; // Recreate array
    }

    // Insere um elemento na posição corrente
    void insert(No* it) {
        Assert(listSize < maxSize, "Capacidade da lista excedida");
        for(int i=listSize; i>curr; i--)
            listArray[i] = listArray[i-1]; // Troca os elementos
        listArray[curr] = it;
        listSize++; // Aumenta o tamanho da lista
    }

    //Insere um elemento no fim da lista
    void append(No* it) {
        Assert(listSize < maxSize, "List capacity exceeded");
        listArray[listSize++] = it;
    }

    // Remove e retorna o elemento corrente
    No* remove() {
        Assert((curr>=0) && (curr < listSize), "No element");
        No* it = listArray[curr]; // Copy the element
        for(int i=curr; i<listSize-1; i++) // Shift them down
            listArray[i] = listArray[i+1];
        listSize--; // Decrement size
        return it;
    }

    //Mover o cursor para o início
    void moveToStart() { curr = 0; }

    //Mover o cursor para o fim
    void moveToEnd() { curr = listSize; }

    //Retrocede o cursor uma posição na lista
    void prev() { if (curr != 0) curr--; }

    //Avança o cursor uma posição na lista
    void next() { if (curr < listSize) curr++; }

    // Retorna o tamanho da lista
    int length() const { return listSize; }

    // Retorna a posição do cursos
    int currPos() const { return curr; }

    // Move o cursor para uma posição determinada
    void moveToPos(int pos) {
        Assert ((pos>=0)&&(pos<=listSize), "Pos out of range");
        curr = pos;
    }

    //Retorna o elemento de uma determianda posição
    No* getValue() {
        Assert((curr>=0)&&(curr<listSize),"No current element");
        return listArray[curr];
    }

    //Recebe a lista
    No** getArray()
    {
        return listArray;
    }
    //Método para imprimira a lista
    void print()
    {
        for(int i= 0;i < listSize; i++)
        {
            cout <<listArray[i]->getContent() << "/" << listArray[i]->getFrequencia() << " ";
        }
        cout << endl;
    }

    //Método para ordernar a lista
    void bubblesort()
    {
        for(int i =0; i < listSize; i++)
        {
            for(int j = i +1; j<listSize; j++)
            {
                if(listArray[i]->getFrequencia() > listArray[j]->getFrequencia())
                {
                    No* temp = listArray[i];
                    listArray[i] = listArray[j];
                    listArray[j] = temp;
                    //swap(listArray[i], listArray[j]);
                }
                else if(listArray[i]->getFrequencia() == listArray[j]->getFrequencia())
                {
                    if(listArray[i]->isLeaf() == true && listArray[j]->isLeaf() == false)
                    {
                        No* temp = listArray[i];
                        listArray[i] = listArray[j];
                        listArray[j] = temp;
                        //swap(listArray[i], listArray[j]);

                    }
                    else if(listArray[i]->isLeaf() == true && listArray[j]->isLeaf() == true)
                    {
                        if(listArray[i]->getContent() > listArray[j]->getContent())
                        {
                            No* temp = listArray[i];
                            listArray[i] = listArray[j];
                            listArray[j] = temp;
                            //swap(listArray[i], listArray[j]);

                        }
                    }

                }
            }
        }
    }


};

#endif // ALIST_H
