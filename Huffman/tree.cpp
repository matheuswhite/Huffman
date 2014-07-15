/* * * * * * * * * * * * * * * * *
*
* CLASSES INCLUSAS
*
* * * * * * * * * * * * * * * * */
#include "tree.h"
#include "No.h"
#include "alist.h"
#include "bitarrays.h"
#include "Pilha.h"

/* * * * * * * * * * * * * * * * *
*
* BIBLIOTECAS
*
* * * * * * * * * * * * * * * * */
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <QString>
#include <QBitArray>

/* * * * * * * * * * * * * * * * *
 *
 * CONSTRUTOR
 *
 * * * * * * * * * * * * * * * * */

Tree::Tree()
{

}

/* * * * * * * * * * * * * * * * *
     *
     * DESTRUTOR
     *
     * * * * * * * * * * * * * * * * */
Tree::~Tree()
{

}
/* * * * * * * * * * * * * * * * *
     *
     * MÉTODOS DA ÁRVORE
     *
     * * * * * * * * * * * * * * * * */




/* * * * * * * * * * * * * * * * *
     *
     * COMPRESSÃO
     *
     * * * * * * * * * * * * * * * * */
//Inicia a árvore
Tree::Tree(int frequencia[], bool compress)
{
    if(compress == true)
    {
        lista = new AList();
        codeNodes = new std::string[256];
        aux = 0;
        sizeTree = 0;
        tree_written.clear();
        buildTree(frequencia);
    }
    else
    {
        root = new No(0,false);
        tree_written.clear();
        sizeTree = 0;
        aux = 0;
        sizeHeader = 0;
        sizeLast = 0;
        sizeFileName = 0;
        sizeTrash = 0;
        filename.clear();
    }
}
//Constrói a árvore
void Tree::buildTree(int frq[])
{
    for(int i = 0; i < 256; i++)
    {
        if(frq[i] != 0)
        {
            No* temp = new No(frq[i], true, i);
            lista->append(temp);
        }
    }

    while(lista->length() > 2)
    {
        //bubblesort
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
        lista->bubblesort();

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
//Codifica os nós da árvore
void Tree::codificar(No *node, std::string temp)
{
    if(node->isLeaf() == true)
    {
        aux = node->getContent();
        codeNodes[aux] = temp;
        //cout << aux << " " << codeNodes[aux].length() << " " << codeNodes[aux] << endl;
    }
    else
    {
        temp = temp + "0";
        codificar(node->getLeftChild(), temp);
        temp = temp.substr(0, temp.length() - 1);
        temp = temp + "1";
        codificar(node->getRightChild(), temp);
    }
}

//Transforma a codificação da árvore em um array de bits
void Tree::codenode_to_bitarray(std::string codenode, bitArrays *buffer)
{
    std::string aux;
    aux = codenode.substr(0, 8);

    std::reverse(aux.begin(), aux.end());

    buffer->setBit(aux, aux.length());
}
//Escreve a árvore
void Tree::writeTree(No *node, std::string temp)
{
    if(node->isLeaf() == true)
    {
        if(node->getContent() == '(')
        {
            tree_written += "$(";
            sizeTree++;
        }
        else if(node->getContent() == ')')
        {
            tree_written += "$)";
            sizeTree++;
        }
        else if(node->getContent() == '$')
        {
            tree_written += "$$";
            sizeTree++;
        }
        else
        {
            tree_written += (char)node->getContent();
            sizeTree++;
        }
    }
    else
    {
        tree_written += "(";
        sizeTree++;
        writeTree(node->getLeftChild(), temp);
        writeTree(node->getRightChild(), temp);
        tree_written += ")";
        sizeTree++;
    }
}

void Tree::equilibrar(std::string tree)
{
    int qabre = 0;
    int qfecha = 0;
    int posA, posF;
    Pilha<char>* verificador = new Pilha<char>();
    char* abre = "(";
    char* fecha = ")";

    for(int i; i < tree.length();i++)
    {

        if(tree[i] == '(')
        {
            qabre++;
            verificador->push(abre);
        }
        else if(tree[i] == ')')
        {
            qfecha++;
            if(verificador->length() != 0)
            {
                if(verificador->topValue() == "(")
                {
                    verificador->pop();
                }
                else
                {
                    verificador->push(fecha);
                }
            }
            else
            {
                verificador->push(fecha);
            }
        }
    }

    int j = verificador->length();
    //cout << "tamanho tree: " << tree.length() << endl;
    //cout << "desequilibrio de: " << j << endl;
    //cout << "qts abre: " << qabre << " qts fecha: " << qfecha << endl;
    //cout << "conteudo: ";
    //for(int i = 0;i < j;i++)
    //{
    //    cout << verificador->pop() << " ";
    //}
    //cout << endl;

    //fazer o equilibrio

}

//Constrói o cabeçalho
void Tree::buildHeader(std::string filename)
{
    std::string aux_s;
    std::string aux_s2;
    bitArrays *bit = new bitArrays();
    int aux_bit;
    int k;

    aux_s.clear();
    writeTree(root, aux_s);
    aux_s.clear();

    //cout << tree_written << endl;

    tree_written = tree_written.substr(1,tree_written.length()-2);

    sizeTree = tree_written.length();
    equilibrar(tree_written);



    switch (sizeTrash) {
    case 1:
        aux_s = "001";
        break;
    case 2:
        aux_s = "010";
        break;
    case 3:
        aux_s = "011";
        break;
    case 4:
        aux_s = "100";
        break;
    case 5:
        aux_s = "101";
        break;
    case 6:
        aux_s = "110";
        break;
    case 7:
        aux_s = "111";
        break;
    case 8:
        aux_s = "000";
    default:
        break;
    }



    aux_bit = sizeTree/2;
    if(sizeTree%2 == 1)
    {
        aux_s2 = "1";
    }
    else if(sizeTree%2 == 0)
    {
        aux_s2 = "0";
    }

    /*
for(int i=0; i < 13; i++)
{
    if(aux_bit == 1)
    {
        aux_s2 += "1";
        break;
    }

    if((aux_bit % 2) == 1)
    {
        aux_s2 += "1";
    }
    else if((aux_bit % 2) == 0)
    {
        aux_s2 += "0";
    }

    aux_bit = aux_bit / 2;
}
*/

    aux_bit = sizeTree;

    while(aux_bit > 1)
    {
        aux_bit = aux_bit/2;
        if(aux_bit % 2 == 1)
        {
            aux_s2 += "1";
        }
        else if(aux_bit % 2 == 0)
        {
            aux_s2 += "0";
        }
    }

    //cout << "string: " << aux_s2 << endl;

    aux_bit = 13 - aux_s2.length();

    reverse(aux_s2.begin(), aux_s2.end());

    //cout << "string2: " << aux_s2 << endl;

    for(int i=0; i < aux_bit; i++)
    {
        aux_s += "0";
    }

    aux_s += aux_s2;

    //cout << "aux_s: " <<aux_s << endl;

    //std::string teste = aux_s.substr(0,8);

    //cout << teste << endl;

    codenode_to_bitarray(aux_s.substr(0,8), bit);

    //cout << "1: " << bit->getArray() << endl;

    codenode_to_bitarray(aux_s.substr(8,8), bit);

    aux_s.clear();

    k = 3 + filename.length() + sizeTree;

    header = new unsigned char[k];

    header = bit->getArray();

    //cout << "header: " << header << endl;

    unsigned char c = filename.length();
    header[2] = c;

    int w =0;
    for(int i =0; i<filename.length();i++)
    {
        w = i +3;
        header[w] = filename[i];
        //    cout << header[w] << " ";
    }
    //cout << endl;

    w = 0;

    int j = 3 + filename.length();

    for(int i = 0;i< sizeTree;i++)
    {
        w = i+j;
        header[w] = tree_written[i];
    }

    sizeHeader = k;
    sizeFileName = filename.length();

    for(int i=0;i<k;i++)
    {
        //cout << "header: " << i << ":" << header[i] << endl;
    }


}
//Escreve o cabeçalho no arquivo
void Tree::writeHeader(char *filename, char *pathOut)
{
    buildHeader(filename);

    ofstream out;
    out.open(pathOut, std::ios::out | std::ios::binary);

    if(out.is_open())
    {
        for(int i=0;i< sizeHeader;i++)
        {
            out << header[i];
        }
    }
    else
    {
        cout << "eRRO!" << endl;
    }
    out.close();
}
//Imprime um nó da árvore
void Tree::printNo(No *node, int level)
{
    if(node != 0)
    {
        printNo(node->getRightChild(), level + 1);
        cout << qPrintable(QString("\t").repeated(level)) << node->getContent() << "/" << node->getFrequencia() << endl;
        printNo(node->getLeftChild(), level + 1);
    }
}

//ajeitar a sobra da string perdida depois de 1024
void Tree::writefile(char *pathIn)
{
    std::ifstream file;
    std::ofstream write;
    std::string aux;
    std::string aux2;
    std::string temporaria;
    int sobra = 0;
    //int z = 0;
    long long int sizefile = 0;
    bitArrays *buffer = new bitArrays();

    aux.clear();
    temporaria.clear();
    codificar(root, aux);
    aux.clear();




    file.open(pathIn , std::ios::in | std::ios::binary | std::ios::ate);

    if(file.is_open())
    {

        int size = file.tellg();
        file.seekg(0, std::ios::beg);
        long int i;



        int iw =1;

        for(i=0; i< size; i++)
        {

            unsigned char c = file.get();
            int j = c;

            aux += codeNodes[j];



            //se >= 1024 kilo-bytes
            if(aux.length() >= 1024*8)
            {


                sobra = aux.length() - 1024*8;

                temporaria = aux.substr(1024*8, sobra);

                for(int k = 0;k < (aux.length()/8); k++)
                {
                    int n = k*8;
                    aux2 = aux.substr(n, 8);


                    codenode_to_bitarray(aux2, buffer);

                }

                iw++;


                write.open("temp.huff", std::ios::out | std::ios::binary | std::ios::app);
                if(write.is_open())
                {
                    for(int z = 0;z < aux.length()/8;z++)
                    {
                        write << buffer->getArray()[z];

                        sizefile++;
                    }

                }


                write.close();

                aux.clear();

                aux = temporaria;



                buffer->clear();
            }
        }



        int y = (aux.length()/8);

        sobra = aux.length() - (y*8);

        aux2 = aux.substr(y*8,sobra);

        std::string teste = aux2;


        for(int k = 0;k < (aux.length()/8); k++)
        {
            int n = k*8;
            aux2 = aux.substr(n, 8);

            codenode_to_bitarray(aux2, buffer);

        }

        int u = 8 - sobra;
        sizeTrash = u;

        aux2 = teste;

        for(int i = 0;i < u;i++)
        {
            aux2 += '0';
        }


        codenode_to_bitarray(aux2, buffer);



        sizeLast = (buffer->getCurrent() / 8);
        sizeLast --;


        write.open("temp.huff", std::ios::out | std::ios::binary | std::ios::app);
        if(write.is_open())
        {
            for(int z=0; z <= sizeLast;z++)
            {
                write << buffer->getArray()[z];

                sizefile++;
            }
        }
        write.close();

        //sizeTrash = buffer->trashLenght();


        buffer->clear();

    }
    else std::cout << "eRRO!" << std::endl;


    file.close();



}

//ajeitar a sobra da string perdida depois de 1024
//Reescreve no arquivo
void Tree::reWriteFile(char *filename, char *pathOut)
{
    writeHeader(filename, pathOut);

    //printNo(root);


    std::ifstream ler;
    std::ofstream write;
    int size2 = 0;
    int sobra =0;

    ler.open("temp.huff", std::ios::in | std::ios::binary | std::ios::ate);



    if(ler.is_open())
    {

        long int size = ler.tellg();
        ler.seekg(0, std::ios::beg);

        unsigned char c[1101*10];
        unsigned char temp[1101*10];


        for(int i=0; i < size; i++)
        {

            c[size2] = ler.get();
            size2++;


            if(size2 == 1024)
            {


                write.open(pathOut, std::ios::out | std::ios::binary | std::ios::app);

                if(write.is_open())
                {


                    for(int j=0 ;j < size2;j++)
                    {
                        write << c[j];

                    }
                    write.close();
                }
                else
                {

                }

                for(int k=0;k < size2;k++)
                {
                    c[k] = 0x0000;

                }

                size2 = 0;
            }
        }

        write.open(pathOut, std::ios::out | std::ios::binary | std::ios::app);

        if(write.is_open())
        {
            for(int j=0 ;j <= sizeLast;j++)
            {
                write << c[j];
            }
            write.close();
        }
        ler.close();
    }
    else
    {
        cout << "eRRO!" << endl;
    }



    if( remove("temp.huff") != 0)
    {
        perror("Erro deleting file");
    }
}
//Verifica se está sobreescrevendo no arquivo
int Tree::checkOverWrite(char *pathOut)
{
    ifstream file;
    file.open(pathOut, std::ios::in | std::ios::binary | std::ios::ate);

    if(file.is_open())
    {
        cout << "eRRO!\tArquivo Existente\n" << endl;
        file.close();
        return -1;
    }
    else
    {
        return 1;
    }
}


/* * * * * * * * * * * * * * * * *
 *
 * DESCOMPRESSÃO
 *
 * * * * * * * * * * * * * * * * */

//Lê o arquivo comprimido
void Tree::readFile(char *pathIn)
{
    std::ifstream file;
    std::string info;

    file.open(pathIn, std::ios::in | std::ios::binary | std::ios::ate);

    if(file.is_open())
    {
        int size = file.tellg();
        file.seekg(0, std::ios::beg);

        for(int i = 0; i < 3; i++)
        {
            info += file.get();

        }

        readHeader(info);

        info.clear();



        for(int i = 0; i < sizeFileName; i++)
        {
            filename += file.get();
        }



        for(int i = 0; i < sizeTree; i++)
        {
            tree_written += file.get();
        }



    }
    else
    {

        cout << "eRRO!" << endl;
    }

    file.close();
}
//Transofrma números binários para decimal
int binarioParaDecimal(std::string str)
{
    reverse(str.begin(), str.end());
    int retorno = 0;
    const char *c;
    c = str.c_str();

    for(int i = 0;i < str.length();i++)
    {
        if(c[i] == '1')
        {
            retorno += pow(2.0,i);
        }
    }

    return retorno;
}
//Transformar um caractere em uma string
std::string charParaString(const unsigned char c)
{
    int byte = (int)c;
    int aux_i;
    std::string retorno;
    retorno.clear();

    aux_i = byte/2;

    if(byte%2 == 1)
    {
        retorno += '1';
    }
    else if(byte%2 == 0)
    {
        retorno += '0';
    }

    aux_i = byte;

    while(aux_i > 1)
    {
        aux_i = aux_i/2;
        if(aux_i%2 == 1)
        {
            retorno += '1';
        }
        else if(aux_i%2 == 0)
        {
            retorno += '0';
        }
    }

    int sobra = 8 - retorno.length();

    if(sobra > 0)
    {
        for(int i = 0; i < sobra;i++)
        {
            retorno += '0';
        }
    }


    reverse(retorno.begin(), retorno.end());

    return retorno;
}

//Lê o cabeçalho do arquivo comprimido
void Tree::readHeader(std::string header)
{
    int byte1 = 0;
    int aux_i = 0;
    const char* c;
    unsigned char aux_uc;
    std::string aux_s, aux_s2;
    std::string trash;
    std::string tree_length;
    aux_s.clear();


    aux_s = header[0];
    c = aux_s.c_str();
    aux_uc = c[0];
    byte1 = (int)aux_uc;

    //byte1 += 127;

    aux_s.clear();




    aux_i = byte1/2;
    if(byte1%2 == 1)
    {
        aux_s += "1";
    }
    else if(byte1%2 == 0)
    {
        aux_s += "0";
    }

    aux_i = byte1;

    while(aux_i > 1)
    {
        aux_i = aux_i/2;
        if(aux_i%2 == 1)
        {
            aux_s += "1";
        }
        else if(aux_i%2 == 0)
        {
            aux_s += "0";
        }
    }



    if(aux_s.length() < 8)
    {
        int j = 0;
        j = 8 - aux_s.length();
        for(int i = 0; i < j;i++)
        {
            aux_s += "0";
        }
    }



    std::reverse(aux_s.begin(),aux_s.end());



    trash = aux_s.substr(0,3);



    sizeTrash = binarioParaDecimal(trash);






    tree_length = aux_s.substr(3,5);



    aux_s2 = header[1];
    const char* ch = aux_s2.c_str();
    const char cz = ch[0];


    tree_length += charParaString(cz);

    sizeTree = binarioParaDecimal(tree_length);



    //errado (header[2])
    aux_s2 = header[2];
    ch = aux_s2.c_str();
    const char cw = ch[0];

    aux_s = charParaString(cw);


    sizeFileName = binarioParaDecimal(aux_s);



    parada = sizeFileName + 3 + sizeTree;


}

//Reconstrói a árvore de Huffmann
void Tree::rebuildTree(std::string maestro)
{
    Pilha<No>* arranjador = new Pilha<No>();

    arranjador->push(root);



    for(int i = 0; i < maestro.length(); i++)
    {

        if(maestro[i] == '$')
        {
            i++;
            if(arranjador->topValue()->getqFilhos() == false)
            {
                No* temp = new No(0,true,maestro[i]);
                arranjador->topValue()->setLeftChild(temp);
                arranjador->topValue()->setqFilhos(true);
            }
            else if(arranjador->topValue()->getqFilhos() == true)
            {
                No* temp = new No(0,true,maestro[i]);
                arranjador->topValue()->setRightChild(temp);
                arranjador->topValue()->setqFilhos(false);
            }
        }
        else
        {
            if(maestro[i] == '(')
            {

                //nenhum filho
                if(arranjador->topValue()->getqFilhos() == false)
                {

                    No* temp = new No(i,false);
                    arranjador->topValue()->setLeftChild(temp);

                    arranjador->topValue()->setqFilhos(true);
                    arranjador->push(temp);
                }
                //1 filho (da esquerda)
                else if(arranjador->topValue()->getqFilhos() == true)
                {
                    No* temp = new No(i,false);
                    arranjador->topValue()->setRightChild(temp);
                    arranjador->topValue()->setqFilhos(false);
                    arranjador->push(temp);
                }
            }
            else if(maestro[i] == ')')
            {
                arranjador->pop();
            }
            else
            {
                if(arranjador->topValue()->getqFilhos() == false)
                {
                    No* temp = new No(0,true,maestro[i]);
                    arranjador->topValue()->setLeftChild(temp);
                    arranjador->topValue()->setqFilhos(true);
                }
                else if(arranjador->topValue()->getqFilhos() == true)
                {
                    No* temp = new No(0,true,maestro[i]);
                    arranjador->topValue()->setRightChild(temp);
                    arranjador->topValue()->setqFilhos(false);
                }
            }
        }
    }


    if(arranjador->length() != 1)
    {
        cout << "eRRO! arvore desequilibrada" << endl;
    }
}
//Procura o elemento que corresponda a uma codificação dada
std::string Tree::procura(string codificacao, int *x)
{
    unsigned char buffer;
    std::string aux_s;
    aux_s.clear();
    ofstream write;
    int j= 0;

    const char* aux_ch = filename.c_str();

    write.open(aux_ch, std::ios::out | std::ios::binary | std::ios::app);


    if(write.is_open())
    {


        Pilha<No>* pilhadeCodigo = new Pilha<No>();
        pilhadeCodigo->push(root);

        for(int i = 0; i < codificacao.length();i++)
        {
            if(j == 100)
            {
                int sobra = 1024 - i;
                aux_s = codificacao.substr(i+1,sobra);

                return aux_s;
            }
            else
            {
                x++;
                //*x += 1;
                No* temp = new No();
                if(codificacao[i] == '0')
                {
                    temp = pilhadeCodigo->topValue()->getLeftChild();
                    if(temp->isLeaf() == false)
                    {
                        pilhadeCodigo->push(temp);
                    }
                    else
                    {
                        buffer = temp->getContent();
                        pilhadeCodigo->clear();
                        pilhadeCodigo->push(root);

                        ;

                        write << buffer;

                        j++;
                        //escrever
                    }
                }
                else if(codificacao[i] == '1')
                {
                    temp = pilhadeCodigo->topValue()->getRightChild();
                    if(temp->isLeaf() == false)
                    {
                        pilhadeCodigo->push(temp);
                    }
                    else
                    {
                        buffer = temp->getContent();
                        pilhadeCodigo->clear();
                        pilhadeCodigo->push(root);

                        write << buffer;



                        j++;
                    }
                }
            }
        }
    }
    else
    {
        cout << "eRRO!" << endl;
    }

    write.close();



    //achar as folhas
    //jogar a folha achada no 'buffer'


    return aux_s;
}

//Procura o último elemento que corresponda a uma codificação dada
std::string Tree::procurafinal(string codificacao)
{
    unsigned char buffer;
    std::string aux_s;
    aux_s.clear();
    ofstream write;

    const char* aux_ch = filename.c_str();

    write.open(aux_ch, std::ios::out | std::ios::binary | std::ios::app);




    if(write.is_open())
    {


        Pilha<No>* pilhadeCodigo = new Pilha<No>();
        pilhadeCodigo->push(root);

        for(int i = 0; i < codificacao.length();i++)
        {


            No* temp = new No();
            if(codificacao[i] == '0')
            {

                temp = pilhadeCodigo->topValue()->getLeftChild();
                if(temp->isLeaf() == false)
                {
                    pilhadeCodigo->push(temp);
                }
                else
                {
                    buffer = temp->getContent();
                    pilhadeCodigo->clear();
                    pilhadeCodigo->push(root);

                    write << buffer;


                }
            }
            else if(codificacao[i] == '1')
            {
                temp = pilhadeCodigo->topValue()->getRightChild();
                if(temp->isLeaf() == false)
                {
                    pilhadeCodigo->push(temp);
                }
                else
                {
                    buffer = temp->getContent();
                    pilhadeCodigo->clear();
                    pilhadeCodigo->push(root);

                    write << buffer;


                }
            }

        }

    }
    else
    {
        cout << "eRRO!" << endl;
    }

    write.close();



    //achar as folhas
    //jogar a folha achada no 'buffer'


    return aux_s;
}

//Reconstrói o arquivo original
void Tree::rebuildOriginalFile(char *pathIn)
{
    std::string info, aux_s,aux_s2;
    std::ifstream file;
    std::string oux, oux2;
    int sobra2 = 0;
    unsigned char* buffer;
    int x = 0;

    info.clear();



    rebuildTree(tree_written);

    //printNo(root);


    equilibrar(tree_written);



    file.open(pathIn, std::ios::in | std::ios::binary | std::ios::ate);


    if(file.is_open())
    {
        int size = file.tellg();
        file.seekg(0, std::ios::beg);

        buffer = new unsigned char[size];

        for(int i = 0; i < parada; i++)
        {
            file.get();
        }



        for(int i = parada;i < size-1;i++)
        {
            unsigned char ch = file.get();
            const unsigned char c = (const unsigned char)ch;



            info += charParaString(c);
            //ajeitar



            /*
        if(info.length() == 1024)
        {
            //sobra2 = info.length() - 1024;
            //oux = info.substr(1024, sobra2);
            //oux2 = info.substr(0,1024);

            aux_s = procura(info,&x);

            cout << "aux_s size: " << aux_s.length() << endl;
            info.clear();

            info += aux_s;
            //info += oux;

            aux_s.clear();
            //oux.clear();
            //oux2.clear();
        }
        */

        }



        //x = info.length();

        int sobra = 1024 - info.length();

        //aux_s = info.substr(x,sobra);
        aux_s = info;



        const char c = file.get();

        aux_s2 = charParaString(c);

        removeTrash(aux_s2);

        aux_s += aux_s2;


        //        cout << "aux_s: ";
        //        for(int i = 0; i < aux_s.length();i++)
        //        {
        //            cout << aux_s[i] << " ";
        //            if((i-1)%8 == 0 && i != 0)
        //            {
        //                cout << endl;
        //                cout << "aux_s: ";
        //            }
        //        }

        procurafinal(aux_s);


    }
    else
    {
        cout << "eRRO!" << endl;
    }

    file.close();

}
//Remove o lixo da string
void Tree::removeTrash(std::string aux_s)
{
    int i = aux_s.length() - sizeTrash;
    aux_s = aux_s.substr(0,i);
}

//Recebe a raiz da árvore
No* Tree::getRoot()
{
    return root;
}
//Recebe a árvore em forma de string
std::string Tree::getTree_written()
{
    return tree_written;
}

void Tree::setTree_written(string tree)
{
    tree_written = tree;
}
