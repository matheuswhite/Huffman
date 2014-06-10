#ifndef TREE_H
#define TREE_H

#include "No.h"
#include "alist.h"
#include "bitarrays.h"

#include <iostream>
#include <fstream>
#include <QString>

using namespace std;


//tirar o using namespace std
class Tree
{
private:
    No* root;
    AList* lista;
    AList* temporaria;

public:
    Tree();

    Tree(int frequencia[])
    {
        lista = new AList();
        temporaria = new AList();
        buildTree(frequencia);
    }

    ~Tree()
    {
        delete [] temporaria;
        delete [] lista;
    }

    //Pronto
    //Falta testar
    void printTree()
    {
        printNo(root);
    }

    //Pronto
    //Falta testar
    void printNo(No* node, int level = 0)
    {
        if(node != 0)
        {
            printNo(node->getRightChild(), level + 1);
            cout << qPrintable(QString("\t").repeated(level)) << node->getContent() << "/" << node->getFrequencia() << endl;
            printNo(node->getLeftChild(), level + 1);
        }
    }

    //Pronto
    //Falta testar
    void buildTree(int frq[])
    {
        for(int i = 0; i < 256; i++)
        {
            if(frq[i] != 0)
            {
                No* temp = new No(frq[i], true, i);
                lista->append(temp);
                temporaria->append(temp);
            }
        }

//        cout << "foi" << endl;

//        lista->moveToStart();
//        for(int i = 0; i < lista->length(); i++)
//        {
//            cout << (int)lista->getValue()->getContent() <<"/"<< lista->getValue()->getContent() << "/" << lista->getValue()->getFrequencia() << " ";
//            lista->next();
//        }

//        cout << "foi2" << endl;

        while(lista->length() > 2)
        {
            //quicksort
            lista->bubblesort();

            //pegando o segundo Nó da lista
            lista->moveToStart();
            lista->next();
            No* temp2 = lista->getValue();

            //criando o Nó pai do primeiro e do segundo Nó
            lista->moveToStart();
            No* temp = new No(lista->getValue()->getFrequencia() + temp2->getFrequencia() , false);
            lista->moveToStart();

            //Setando os dois filhos
            temp->setFilhos(lista->getValue(), temp2);
            lista->moveToStart();

            //Excluindo os dois filhos
            lista->remove();
            lista->moveToStart();
            lista->remove();
            lista->moveToStart();

            //inserindo o Nó pai
            lista->insert(temp);
        }

        if(lista->length() == 2)
        {
            //Pegando o segundo elemento
            lista->moveToStart();
            lista->next();
            No* temp2 = lista->getValue();

            //criando o Nó Raiz
            lista->moveToStart();
            root = new No(lista->getValue()->getFrequencia() + temp2->getFrequencia(), false);
            lista->moveToStart();

            //Setando os dois filhos do Nó raiz
            root->setFilhos(lista->getValue(), temp2);
            lista->moveToStart();
        }
        else
        {
            std::cout << "eRRO!" << std::endl;
        }
    }

    //setar o codigo das folhas(Nó)
    //Pronto
    //Falta testar
    void setChildCode()
    {
        temporaria->moveToStart();
        std::string aux;
        for(int i = 0; i<temporaria->length(); i++)
        {
            aux.clear();
            aux = coding(root, aux, temporaria->getValue()->getContent());
            temporaria->getValue()->setCode(aux);
            temporaria->next();
        }

    }

    //pega o codigo de cada nó apartir da arvore e coloca numa string
    //Pronto
    //Falta testar
    std::string coding(No* node, std::string temp, unsigned char content)
    {
        bool wentLeft = false;
        if(!wentLeft)
        {
            if(node->getContent() != content)
            {
                temp += "0";
                return coding(node->getLeftChild(), temp , content);
            }
            if(node->getContent() == content && node->isLeaf() == true)
            {
                return temp += "0";
            }
            else
            {
                wentLeft = true;
                temp = temp.substr(0, temp.length() - 1);
                return temp;
            }
        }
        if(wentLeft)
        {
            if(node->getContent() != content)
            {
                temp += "1";
                return coding(node->getRightChild(), temp, content);
            }
            if(node->getContent() == content && node->isLeaf() == true)
            {
                return temp += "1";
            }
            else
            {
                wentLeft = false;
                temp = temp.substr(0, temp.length() - 1);
                return temp;
            }
        }
        return temp;
    }

    //transformar o codigo de string para bitarray
    //Pronto
    //Falta testar
    unsigned char* codificar(unsigned char x)
    {
        std::string aux = find(x);
        std::string aux2;
        bitArrays *b = new bitArrays();


        aux2.clear();
        for(int i =0; i< aux.length(); i++)
        {
            aux2 = aux.substr(i,1);
            if(aux2 == "1")
            {
                b->setBit(i);
            }
        }
        return b->getArray();
    }

    //escrever o codigo num arquivo
    //Quanse pronto
    //Falta testar
    void writefile(char* pathIn, char* pathOut, char* nameFile)
    {
        std::ifstream file;
        std::ofstream write;
        int y;
        unsigned char* buffer;

        file.open(pathIn , std::ios::in | std::ios::binary | std::ios::ate);

        if(file.is_open())
        {
            int size = file.tellg();
            file.seekg(0, std::ios::beg);

            for(int i=0; i< size; i++)
            {
                unsigned char x = file.get();
                write.open(pathOut, std::ios::out | std::ios::binary | std::ios::);
                //buffer < 104
                if()
                {
                    buffer += codificar(x);
                }
                //buffer >= 104
                else
                {
                    //escrever no arquivo o buffer
                }
                write.close();
            }
        }
        else std::cout << "eRRO!" << std::endl;

        file.close();
    }

    //achar o codigo de um determinado Nó numa lista(temporaria)
    //Pronto
    //Falta testar
    std::string find(unsigned char content)
    {
        temporaria->moveToStart();
        for(int i=0;i<lista->length();i++)
        {
            if(temporaria->getValue()->getContent() == content)
            {
                return temporaria->getValue()->getCode();
            }
            temporaria->next();
        }
    }

    //Pronto
    //Testado;
    No* getRoot()
    {
        return root;
    }
};

#endif // TREE_H
