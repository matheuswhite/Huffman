#ifndef HEAP_H
#define HEAP_H

#include <iostream>

using namespace std;

template <typename E>
class heap
{
private:
    E* Heap;
    int maxsize;
    int n;

    void heapfy(int pos)
    {
        while (!isLeaf(pos))
        {
            int lr = left(pos);
            int rc = righ(pos);
            if ((rc < n) && prior(Heap[rc], Heap[lr]))
            {
                lr = rc;
            }
            if (prior(Heap[pos], Heap[lr]))
            {
                return;
            }
            swap(Heap, pos, lr);
            pos = lr;
        }
    }


public:
    bool prior(const E& first, const E& second)
    {
        if(first > second)
        {
            return true;
        }
        return false;
    }

    void swap(E* h ,E first, E second)
    {
        E aux = h[first];
        h[first] = h[second];
        h[second] = aux;
    }

    void Assert(const bool& condition, const char* msg)
    {
        if(condition == false)
        {
            cout << msg << endl;
        }
        return;
    }

    void bubble(int curr)
    {
        while ((curr!=0) &&
               (prior(Heap[curr], Heap[parent(curr)])))
        {
            swap(Heap, curr, parent(curr));
            curr = parent(curr);
        }
    }

    void buildMaxHeap()
    {
        for (int i=n/2-1; i>=0; i--)
        {
            heapfy(i);
        }
    }

    heap(E* h, int num, int max)
    {
        Heap = h;
        n = num;
        maxsize = max;
        buildMaxHeap();
    }

    ~heap()
    {
        delete [] Heap;
    }

    void print() const
    {
        for(int i = 0; i<n;++i)
        {
            cout << Heap[i] << " ";
        }
        cout << "\n";
    }

    int size() const
    {
        return n;
    }

    bool isLeaf(int pos) const
    {
        return (pos >= n/2) && (pos < n);
    }

    int left(int pos) const
    {
        return 2*pos + 1;
    }

    int righ(int pos) const
    {
        return 2*pos + 2;
    }

    int parent(int pos) const
    {
        return (pos-1)/2;
    }


    void insert(const E& it) {
        Assert(n < maxsize, "Heap is full");
        int curr = n++;
        Heap[curr] = it;
        bubble(curr);
    }

    E removefirst() {
        Assert (n > 0, "Heap is empty");
        swap(Heap, 0, --n);
        if (n != 0)
        {
            heapfy(0);
        }
        return Heap[n];
    }

    E remove(int pos) {
        Assert((pos >= 0) && (pos < n), "Bad position");
        if (pos == (n-1))
        {
            n--;
        }

        else
        {
            swap(Heap, pos, --n);
            bubble(pos);
            if (n != 0)
            {
                heapfy(pos);
            }
        }

        return Heap[n];
    }

};

#endif // HEAP_H
