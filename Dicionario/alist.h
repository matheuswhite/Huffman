#ifndef ALIST_H
#define ALIST_H

#include <iostream>
#include "No.h"

//Ajeitar o quicksort
 // Array-based list implementation
class AList {
private:
    int maxSize; // Maximum size of list
    int listSize; // Number of list items now
    int curr; // Position of current element
    No** listArray; // Array holding list elements

public:
    AList(int size=0) { // Constructor
        maxSize = 256;
        listSize = curr = 0;
        listArray = new No*[maxSize];
    }
    ~AList() { delete [] listArray; } // Destructor

    int Assert(bool condition, std::string name)
    {
        if(condition == false)
        {
            return -71;
        }
    }

    void clear() { // Reinitialize the list
        delete [] listArray; // Remove the array
        listSize = curr = 0; // Reset the size
        listArray = new No*[maxSize]; // Recreate array
    }

    // Insert "it" at current position
    void insert(No* it) {
        Assert(listSize < maxSize, "List capacity exceeded");
        for(int i=listSize; i>curr; i--) // Shift elements up
            listArray[i] = listArray[i-1]; // to make room
        listArray[curr] = it;
        listSize++; // Increment list size
    }

    void append(No* it) { // Append "it"
        Assert(listSize < maxSize, "List capacity exceeded");
        listArray[listSize++] = it;
    }

    // Remove and return the current element.
    No* remove() {
        Assert((curr>=0) && (curr < listSize), "No element");
        No* it = listArray[curr]; // Copy the element
        for(int i=curr; i<listSize-1; i++) // Shift them down
            listArray[i] = listArray[i+1];
        listSize--; // Decrement size
        return it;
    }

    void moveToStart() { curr = 0; } // Reset position

    void moveToEnd() { curr = listSize; } // Set at end

    void prev() { if (curr != 0) curr--; } // Back up

    void next() { if (curr < listSize) curr++; } // Next

    // Return list size
    int length() const { return listSize; }

    // Return current position
    int currPos() const { return curr; }

    // Set current list position to "pos"
    void moveToPos(int pos) {
        Assert ((pos>=0)&&(pos<=listSize), "Pos out of range");
        curr = pos;
    }

    No* getValue() { // Return current element
        Assert((curr>=0)&&(curr<listSize),"No current element");
        return listArray[curr];
    }

    No** getArray()
    {
        return listArray;
    }

    No** swapNo(No* array[], No* primeiro, No* segundo)
    {
        if(primeiro->getFrequencia() > segundo->getFrequencia())
        {
            No* temp = primeiro;
            primeiro = segundo;
            segundo = temp;
        }
        else if(primeiro->getFrequencia() == segundo->getFrequencia())
        {
            if(primeiro->isLeaf() == true && segundo->isLeaf() == false)
            {
                No* temp = primeiro;
                primeiro = segundo;
                segundo = temp;
            }
        }
    }

    void bubblesort()
    {
        for(int i =0; i < listSize; i++)
        {
            for(int j = i +1; j< listSize; j++)
            {
                swapNo(listArray, listArray[i], listArray[j]);
            }
        }
    }


};

#endif // ALIST_H
