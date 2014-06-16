#include "tree.h"

//Tirar o using namespace std
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


//        for(int i=0;i<256;i++)
//        {
//            std::cout << i << "/"<< freq[i] << " ";
//        }
//        std::cout << "\n";


    }
    else std::cout << "eRRO!" << std::endl;

    file.close();
}


int main()
{

    int freq[256] = {0};
    char* caminho;

    readfile("bola.png", freq);

    Tree* huffman = new Tree(freq);

    huffman->printTree();




    return 0;
}
