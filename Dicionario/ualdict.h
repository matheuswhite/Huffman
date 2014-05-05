#ifndef UALDICT_H
#define UALDICT_H

#include "dictionary.h"
#include "alist.h"
#include "kvpair.h"

template <typename Key, typename E>
class UALdict : public Dictionary<Key, E> {
private:
    AList<KVpair<Key,E> >* list;
public:
    UALdict(int size = 0) // Constructor
    {
        list = new AList<KVpair<Key,E> >(size);
    }
    ~UALdict() { delete list; } // Destructor


    void clear() { list->clear(); } // Reinitialize

    // Insert an element: append to list
    void insert(const Key& k, const E& e) {
        KVpair<Key,E> temp(k, e);
        list->append(temp);
    }

    // Use sequential search to find the element to remove
    E remove(const Key& k) {
        E temp = find(k); // "find" will set list position
        if(temp != 0)
        {
            list->remove();
        }
        return temp;
    }

    E removeAny() { // Remove the last element
        Assert(size() != 0, "Dictionary is empty");
        list->moveToEnd();
        list->prev();
        KVpair<Key,E> e = list->remove();
        return e.value();
    }

    // Find "k" using sequential search
    E find(const Key& k) const {
        for(list->moveToStart(); list->currPos() < list->length(); list->next()) {
            KVpair<Key,E> temp = list->getValue();
            if (k == temp.key())
            {
                return temp.value();
            }
        }
        return 0; // "k" does not appear in dictionary
    }

    int size() // Return list size
    { return list->length(); }

    void setFreqDict(char* cadeia, int size)
    {
        char aux[size];
        aux[0] = cadeia[0];
        int j=1;

        for(int i=1;i<size;++i)
        {
            for(int k=0;k<i;++k)
            {
                if(cadeia[k] != cadeia[i])
                {
                    if(k==i-1)
                    {
                        aux[j] = cadeia[i];
                        k=i+1;
                        j++;
                    }
                }
                else
                {
                    k=i+1;
                }
            }
        }

        int i=0;
        while(aux[i] != '\0')
        {
            insert(aux[i], freq(aux[i], cadeia, size) );
            i++;
        }

//        for(i=0;i<sizeStr(aux);++i)
//        {
//            cout << find(aux[i]) << " ";
//        }
//        cout << "\n";
    }

};

#endif // UALDICT_H
