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
    std::string* codeNodes;

public:
    Tree();

    Tree(int frequencia[])
    {
        lista = new AList();
        buildTree(frequencia);
    }

    ~Tree()
    {
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
            //lista->print();

            //pegando o segundo Nó da lista
            lista->moveToStart();
            //cout << lista->getValue()->getContent() << "/" ;
            lista->next();
            No* temp2 = lista->getValue();

            //cout << temp2->getContent() << " " ;

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

    //pega o codigo de cada nó apartir da arvore e coloca numa string
    //Pronto
    //Falta testar
    std::string codingNodes(No* node, std::string aux)
    {

        if(root->getLeftChild()->getFind()== false || root->getRightChild()->getFind() ==false)
        {
            if (node->getLeftChild()->getFind()== false)
            {
                if(node->getLeftChild()->isLeaf()==true)
                {
                    aux +="0";
                    node->getLeftChild()->setFind(true);
                    int i = node->getLeftChild()->getContent();
                    codeNodes[i] = aux;
                    cout << i << "/" << codeNodes[i] << " ";
                    aux.clear();
                    return aux;

                }
                else
                {
                    aux += "0";
                    return (node->getLeftChild(), aux );
                }

            }
            else if(node->getLeftChild()->getFind() ==true && node->getRightChild()->getFind()==false)
            {
                if(node->getRightChild()->isLeaf()==true)
                {
                    aux +="1";
                    node->getLeftChild()->setFind(true);
                    int i = node->getLeftChild()->getContent();
                    codeNodes[i] = aux;
                    cout << i << "/" << codeNodes[i] << " ";
                    aux.clear();
                    return aux;

                }
                else
                {
                    aux += "0";
                    return (node->getRightChild(), aux );
                }


            }
            else if(node->getLeftChild()->getFind() == true && node->getLeftChild()->getFind() ==true)
            {
                node->setFind(true);
                aux.clear();
                return aux;

            }


        }

        return 0;
    }

    std::string codingNo(No* node, std::string temp, unsigned char letter)
    {
        //String temp = "";
        bool wentLeft = false;
        if(node->isLeaf() == false && !wentLeft)
        {
            if(node->getLeftChild()->isLeaf() == false)
            {
                temp = temp + "0";
                return codingNo(node->getLeftChild(), temp, letter);
            }
            if(node->getLeftChild()->getContent() == letter)
            {
                return temp = temp + "0";
            }
            else
            {
                wentLeft = true;
                temp = temp.substr(0, temp.length() - 1);
                return temp;
            }
        }
        if(node->isLeaf() == false && wentLeft)
        {
            if(node->getRightChild()->isLeaf() == false)
            {
                temp = temp + "1";
                return codingNo(node->getRightChild(), temp, letter);
            }
            if(node->getRightChild()->getContent() == letter)
            {
                return temp = temp + "1";
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
    //Ajeitar
    //Falta testar
    void codenode_to_bitarray(std::string codenode, bitArrays *buffer)
    {

        std::string aux;



        for(int i =0; i< codenode.length(); i++)
        {
            aux = codenode.substr(i,1);
            if(aux == "1")
            {
                buffer->setBit(i);

            }



        }

        return ;
    }

    //escrever o codigo num arquivo
    //Ajeitar
    //Falta testar
    void writefile(char* pathIn, char* pathOut, char* nameFile)
    {
        std::ifstream file;
        std::ofstream write;
        std::string aux;
        long int sizebuffer;
        bitArrays *buffer = new bitArrays();

        aux.clear();
        codingNodes(root, aux);
        //codingNo(root, aux);

        return ;

        file.open(pathIn , std::ios::in | std::ios::binary | std::ios::ate);

        if(file.is_open())
        {
            int size = file.tellg();
            file.seekg(0, std::ios::beg);

            for(int i=0; i< size; i++)
            {
                unsigned char c = file.get();
                int j = c;


                codenode_to_bitarray(codeNodes[j], buffer);
                //quando o buffer for 1MB escreve no arquivo
                if(buffer->lenghtbit() >= (1024*8))
                {
                    write.open(pathOut, std::ios::out | std::ios::binary | std::ios::app);
                    if(write.is_open())
                    {
                        write << buffer;
                    }

                    write.close();

                    buffer->clear();
                }
            }
            write.open(pathOut, std::ios::out | std::ios::binary | std::ios::app);
            if(write.is_open())
            {
                write << buffer;

            }
            write.close();

            buffer->clear();

        }
        else std::cout << "eRRO!" << std::endl;

        file.close();
    }

    //Pronto
    //Testado;
    No* getRoot()
    {
        return root;
    }
};

#endif // TREE_H
