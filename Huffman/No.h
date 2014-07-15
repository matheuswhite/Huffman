#ifndef NO_H
#define NO_H

    /* * * * * * * * * * * * * * * * *
    *
    * BIBLIOTECAS
    *
    * * * * * * * * * * * * * * * * */

#include <iostream>

class No
{
private:

    /* * * * * * * * * * * * * * * * *
    *
    * MEMBROS DA CLASSE
    *
    * * * * * * * * * * * * * * * * */


    No* left; //Filho esquerdo
    No* right; //Filho direito
    int frequencia; //Frequência associada ao nó
    bool leaf; //Variável que indica se o nó é uma folha
    bool find; //Variável que indica se o nó já foi encontrado
    bool qFilhos; //Variável
    int checkedChild;
    unsigned char content;

public:

    /* * * * * * * * * * * * * * * * *
    *
    * CONSTRUTORES
    *
    * * * * * * * * * * * * * * * * */

    No()
    {
        qFilhos = false;
        checkedChild = 0;
    }

    No(int  freq, bool l, unsigned char cont = 0)
    {
        find = false;
        frequencia = freq;
        content = cont;
        leaf = l;
        left = 0;
        right = 0;
        qFilhos = false;
        checkedChild = 0;
    }


    /* * * * * * * * * * * * * * * * *
    *
    * DESTRUTOR
    *
    * * * * * * * * * * * * * * * * */

    ~No() {}

    /* * * * * * * * * * * * * * * * *
     *
     * MÉTODOS DO NÓ
     *
     * * * * * * * * * * * * * * * * */

    void setCheckedChild(int val)
    {
        checkedChild = val;
    }

    int getCheckedChild()
    {
        return checkedChild;
    }

    //"Seta" o valor booleano dos filhos
    void setqFilhos(bool valqFilhos)
    {
        qFilhos = valqFilhos;
    }

    //Retorna o valor boolenao dos filhos
    bool getqFilhos()
    {
        return qFilhos;
    }

    //Muda o valor da variavel find
    void setFind(bool con)
    {
        find = con;
    }

    //Recebe o valor da variável find
    bool getFind()
    {
        return find;
    }

    //Recebe o valor da vairável frequência
    int getFrequencia()
    {
        return frequencia;
    }

    //Recebe o  valor da variável content (conteúdo do nó)
    unsigned char getContent()
    {
        return content;
    }

    //Método booleano para identificar uma folha
    bool isLeaf()
    {
        return leaf;
    }

    //Seta os filhos do nó
    void setFilhos(No* esq, No* dir)
    {
        left = esq;
        right = dir;
    }

    //Seta os filhos da esquerda
    void setLeftChild(No* esq)
    {
        left = esq;
    }

    //Seta os filhos da direita
    void setRightChild(No* dir)
    {
        right = dir;
    }

    //Recebe o filho da esquerda
    No* getLeftChild()
    {
        return left;
    }
    //Recebe o filho da direita
    No* getRightChild()
    {
        return right;
    }

};

#endif // NO_H
