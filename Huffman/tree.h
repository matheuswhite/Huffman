#ifndef TREE_H
#define TREE_H

    /* * * * * * * * * * * * * * * * *
    *
    * BIBLIOTECAS
    *
    * * * * * * * * * * * * * * * * */
#include "No.h"
#include "alist.h"
#include "bitarrays.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <QString>
#include <QBitArray>

using namespace std;

class Tree
{
private:

    /* * * * * * * * * * * * * * * * *
     *
     * MEMBROS DA CLASSE
     *
     * * * * * * * * * * * * * * * * */

    No* root; //Nó raiz da árvore
    AList* lista; //Lista que contém os nós da árvore
    std::string* codeNodes; //String que contém a codificação de cada nó
    std::string tree_written; //String que contém a árvore montade
    int aux;
    int sizeHeader; //Tamanhdo do cabeçalho
    int sizeLast; //Tamanho do último
    int sizeFileName;//Tamanho do arquivo
    int parada; // Parada recursão
    unsigned short sizeTree; //Tamanho da árvores
    unsigned short sizeTrash; //Tamanho do lixo
    unsigned char* header; //Cabeçalho do arquivo
    std::string filename; //Nome do arquivo

public:

    /* * * * * * * * * * * * * * * * *
     *
     * CONSTRUTORES
     *
     * * * * * * * * * * * * * * * * */
    Tree();
    Tree(int frequencia[]=0, bool compress = true);

    /* * * * * * * * * * * * * * * * *
     *
     * DESTRUTORES
     *
     * * * * * * * * * * * * * * * * */

    ~Tree();

    /* * * * * * * * * * * * * * * * * * * * *
     *
     * COMPRESSÃO
     *
     * * * * * * * * * * * * * * * * * * * * */

private:
    //Constrói a Árvore de Huffmann
    void buildTree(int frq[]);
    //Atribui uma codificação a cada nó
    void codificar(No* node, std::string temp);
    //Transforma o codigo de string para bitarray
    void codenode_to_bitarray(std::string codenode, bitArrays *buffer);
    //representa a árvore numa string
    void writeTree(No* node, std::string temp);
    // Constrói o cabeçalho
    void buildHeader(std::string filename);
    // Escreve o cabeçalho no arquivo
    void writeHeader(char* filename, char* pathOut);

public:
    //Imprime a Árvore
    void printNo(No* node, int level = 0);
    //Escreve o codigo no arquivo temporario
    void writefile(char* pathIn);
    //Rescreve o codigo no arquivo permanente
    void reWriteFile(char* filename, char* pathOut);
    // Checa se o arquivo já existe
    int checkOverWrite(char* pathOut);

    /* * * * * * * * * * * * * * * * * *
     *
     * DESCOMPRESSÃO
     *
     * * * * * * * * * * * * * * * * * */

private:

public:
    //Lê o arquivo a ser descomprimido
    void readFile(char* pathIn);
    //Lê o cabeçalho do arquivo a ser descoprimido
    void readHeader(std::string header);
    //Reconstrói a árvore de Huffmann
    void rebuildTree(std::string maestro);
    //Procura o elemento na árvore, segundo a codificação dada
    string procura(std::string codificacao, int *x);
    //Procura o último elemento na árvore
    string procurafinal(std::string codificacao);
    //Reconstrói o arquivo original
    void rebuildOriginalFile(char *pathIn);
    //Remove o lixo
    void removeTrash(std::string aux_s);

    /* * * * * * * * * * * * * * * * * *
     *
     * UTILITARIOS
     *
     * * * * * * * * * * * * * * * * * */

public:
    //Recebe a raiz da árvore
    No* getRoot();
    //Recebe a árvore em forma de string
    std::string getTree_written();

    void setTree_written(std::string tree);

    void equilibrar(std::string tree);

    int getfilenameSize()
    {
        return sizeFileName;
    }
};

#endif // TREE_H
