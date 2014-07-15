/* * * * * * * * * * * * * * * * *
        *
        * CLASSES INCLUSAS
        *
        * * * * * * * * * * * * * * * * */

#include "tree.h"
#include <QtCore>
#include <string.h>
#include <QString>



/* * * * * * * * * * * * * * * * *
    *
    * MÉTODOS
    *
    * * * * * * * * * * * * * * * * */
//Lê o arquivo
void readfile(char* path, int freq[])
{
    std::ifstream file;
    int y;

    file.open(path , std::ios::in | std::ios::binary | std::ios::ate);

    if(file.is_open())
    {
        int size = file.tellg();
        file.seekg(0, std::ios::beg);


        for(int i=0; i< size; i++)
        {
            unsigned char x = file.get();
            y = x;
            (freq[y])++;
        }
    }
    else
    {
        std::cout << "eRRO!1" << std::endl;
    }

    file.close();
}

void integridade(char* path1, char* path2)
{
    std::ifstream file1;
    std::ifstream file2;
    std::string buffer1;
    std::string buffer2;
    int x = 0;
    int y = 0;
//    int k = 0;

    file1.open(path1, std::ios::in | std::ios::binary | std::ios::ate);
    file2.open(path2, std::ios::in | std::ios::binary | std::ios::ate);

    if(file1.is_open())
    {
        if(file2.is_open())
        {
            int size1 = file1.tellg();
            int size2 = file2.tellg();

            file1.seekg(0, std::ios::beg);
            file2.seekg(0, std::ios::beg);

            if(size1 != size2)
            {

            }
            for(int i =0 ; i < size1; i++)
            {
                buffer1 += file1.get();
                buffer2 += file2.get();

                if(buffer1.length() == 1024*8)
                {
                    if(buffer1.compare(buffer2) == 0)
                    {
                        cout << "Iguais até aki!" << endl;
                    }
                    else
                    {
                        for(int j = 0; j < 1024; j++)
                        {
                            if(buffer1[j] != buffer2[j])
                            {
                                cout << "Diferença na posição: "<< j+x << endl;
                                cout << "Buffer1: " << buffer1[j] << " Buffer2: " << buffer2[j] << endl << endl;
                                break;
                            }
                            else
                            {
                                //cout << "Sem diferença na posição: "<< j+x << endl;
                                //cout << "Buffer1: " << buffer1[j+k] << " Buffer2: " << buffer2[j] << endl << endl;
                            }
                            y = j;
                        }
                        x = y;
                        //break;
                    }

                    buffer1.clear();
                    buffer2.clear();
                }
            }

        }
        else
        {
            cout << "eRRo - Arquivo 2 não pode ser aberto" << endl;
        }
    }
    else
    {
        cout << "eRRo - Arquivo 1 não pode ser aberto!" << endl;
    }

    file2.close();
    file1.close();
}


int main(int argc, char* argv[])
{
    int freq[256] = {0};
//    char* caminho;
//    char* buffer;
    std::string aux, aux2,aux5;

//    int tamanho;







    /* * * * * * * * * * * * * * * * *
    *
    * COMPRESSÃO
    *
    * * * * * * * * * * * * * * * * */
    if(argc == 5)
    {
        if(argv[1] != "-c")
        {
            if(argv[3] != "-o")
            {
                aux = argv [4] ;
                aux = aux.substr(aux.length() - 5, 5);



                if(strcmp(aux.c_str(), ".huff") == 0)
                {

                    readfile(argv[2], freq);

                    Tree* huffman = new Tree(freq);

                    huffman->writefile(argv[2]);

                    huffman->reWriteFile(argv[2], argv[4]);

                    cout << "Comprimido!!!!!" << endl;


                }
                else
                {
                    cout << "eRRO! A extensão do arquivo de saída deverá ser '.huff' " << endl;
                }
            }
            else
            {
                cout << "eRRO!Digite o comando -o após o nome do arquivo original." << endl;
            }
        }
        else
        {
            cout << "eRRO! Digite o comando -c antes do nome do arquivo original" << endl;
            //help
        }
    }
    else if(argc == 3)
    {

        if(argv[1] != "-c")
        {
            aux5 = argv[2];
            int x= aux5.length();
            std::size_t found = aux5.find(".");
            aux5 = aux5.substr(0, found);
            aux5 += ".huff";

           //cout << "AUX5: " << aux5 << endl;

            char* saida = new char[aux5.length() + 1];
            strcpy(saida, aux5.c_str());

            readfile(argv[2], freq);

            Tree* huffman = new Tree(freq);

            huffman->writefile(argv[2]);

            huffman->reWriteFile(argv[2], saida);

            cout << "Comprimido!" << endl;


            delete [] saida;
        }
        else
        {
            cout << "eRRo!! Digite o comando -c antes do nome do arquivo original" << endl;

        }
    }

        /* * * * * * * * * * * * * * * * *
        *
        * DESCOMPRESSÃO
        *
        * * * * * * * * * * * * * * * * */

    else if (argc == 2)
    {

        aux2 = argv[1];
        aux2 = aux2.substr(aux2.length() - 5, 5);


        if(aux2 == ".huff")
        {

            Tree* deHuffman = new Tree(0, false);

            deHuffman->readFile(argv[1]);

            //deHuffman->rebuildTree(deHuffman->getTree_written());

            deHuffman->rebuildOriginalFile(argv[1]);

            cout << "Descomprimido" << endl;
        }
        else
        {
            cout << "eRRO! A extensão do arquivo de entrada deverá ser '.huff' " << endl;
        }
    }
    else if(argc == 4)
    {

        if (argv[2] == " -d")
        {
            if(aux2 == ".huff")
            {
                char* aux3 ;
                aux3 = argv[3];
                char* aux4;
                aux4 = argv[1];
                strcat(aux3,aux4);


                Tree* deHuffman = new Tree(0, false);

                deHuffman->readFile(aux3);

                //deHuffman->rebuildTree(deHuffman->getTree_written());

                deHuffman->rebuildOriginalFile(aux3);
                cout << "Descomprimido" << endl;

            }

            else
            {

                cout << "eRRO! A extensão do arquivo de entrada deverá ser '.huff'" << endl;

            }
        }
        else
        {
            cout << "eRRO!Digite o comando -d após o nome do arquivo" << endl;
        }
    }

    return 0;
}
