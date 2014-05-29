#include <iostream>
#include <fstream>

using namespace std;

void readfile(char* path, int *freq)
{
    ifstream file;
    int y;

    file.open(path , ios::in | ios::binary | ios::ate);

    if(file.is_open())
    {
        int size = file.tellg();
        file.seekg(0, ios::beg);


        for(int i=0; i< size; i++)
        {
            unsigned char x = file.get();
            y = x;
            (freq[y])++;
        }

        /*
        for(int i=0;i<256;i++)
        {
            cout << freq[i] << " ";
        }
        cout << "\n";
        */
    }
    else cout << "eRRO!" << endl;

    file.close();
}

int main()
{
    int freq[256] = {0};
    char* caminho;

    readfile("bola.png", freq);




//    ifstream myfile;
//    char* line;
//    long size;

//    myfile.open("bola.png", ios::in| ios::binary| ios::ate);

//    if(myfile.is_open())
//    {
//        size = myfile.tellg();
//        myfile.seekg(0, ios::beg);
//        line = new char[size];

//        myfile.read(line, size);
//        myfile.close();

//    }
//    else cout << "Unable to open file" << endl;

//    ofstream outfile("bola1.png", ios::out | ios::binary);

//    outfile.write(line, size);
//    cout << "Gravou!" << endl;
//    myfile.close();


    return 0;
}
