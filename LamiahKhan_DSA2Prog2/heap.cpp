/* Lamiah Khan DSA II, 10/10/2024
 Credits: hash.cpp was implemented from Project 1. 
 Any resources used will be linked to within the document.*/


#include "heap.h"

using namespace std;
// The following was used for the heap.cpp, and then editted. 
//https://www.geeksforgeeks.org/cpp-stl-heap/
// Sets up space for nodes in the vector, "data" & initializes has table for mapping
heap::heap(int capacity):mapping(capacity*2){
    // Note: 0 slot is not used
    this->capacity = capacity;
    this->stored = 0;
    data.resize(capacity+1);
    mapping = hashTable(capacity*2);
}

// Inserts new node w/ specified id, key, and optional data pointer (pv)
// 0 = successful, 1 = heap @ capacity, 2 = id exists in heap
int heap::insert(const string &id, int key, void *pv){
    if(stored >= capacity){
        return 1;
    }
    else if(mapping.contains(id)){
        return 2;
    }
    stored++;
    data[stored].id = id;
    data[stored].key = key;
    data[stored].pData = pv;
    // maps id to new node
    mapping.insert(id, &data[stored]);
    // Restores the heap by percolating up
    percolateUp(stored);
    return 0;
}

// Deletes min node in heap and provides id, key, and desired data. 
// 0 = success, 1 = heap is empty
// Link: https://www.programiz.com/dsa/heap-data-structure
int heap::deleteMin(string *ptrId, int *ptrKey, void *ppData){
    if(stored==0){
        return 1;
    }
    if(ptrId){
        *ptrId = data[1].id;
    }
    if(ptrKey){
        *ptrKey = data[1].key;
    }
    if(ppData){
        *(static_cast<void **> (ppData)) = data[1].pData;
    }
    // Restores heap order by precolating down from root. 
    mapping.remove(data[1].id);
    data[1] = data[stored--];
    mapping.setPointer(data[1].id, &data[1]);
    percolateDown(1);
    return 0;
}

// Updates key of specified id, preserving heap order by percolating up or down. 
// 0 = sucessful, 1 = id not found
// Link: https://www.programiz.com/dsa/heap-data-structure
// Video (in python, but I implemented strategy for c++): https://www.youtube.com/watch?v=UFyTksTXFTA&t=2s
int heap::setKey(const string &id, int key){
    bool b = false;
    node *pn = static_cast<node *> (mapping.getPointer(id, &b));
    if(!b){
        return 1;
    }
    int i = returnPosition(pn);
    data[i].key = key;
    if(checkPercDown(i)){
        percolateDown(i);
    }
    else if(checkPercUp(i)){
        percolateUp(i);
    }
    return 0;
}

// Removes the node w/ specified id from heap, providing key and desired data. 
// false = successful; true = id is not found
int heap::remove(string id, int *key, void *ppData){
    bool b = false;
    node *pn = static_cast<node *> (mapping.getPointer(id, &b));
    if(!b){
        return true;
    }
    int i = returnPosition(pn);
    if(key){
        *key = data[i].key;
    }
    mapping.remove(data[i].id);
    data[i] = data[stored--];
    mapping.setPointer(data[i].id, &data[i]);
    if(checkPercDown(i)){
        percolateDown(i);
    }
    else if(checkPercUp(i)){
        percolateUp(i);
    }
    return false;
}

// Percolates a node up until heap order is restored. 
// cPos = current note position 
void heap::percolateUp(int cPos){
    while(cPos > 1 && data[cPos].key < data[cPos/2].key){
        swap(data[cPos], data[cPos/2]);
        mapping.setPointer(data[cPos].id, &data[cPos]);
        mapping.setPointer(data[cPos/2].id, &data[cPos/2]);
        cPos /= 2;
    }
}

// Two children are compared, node is swapped with smallest, percolates node down until heap order property is restored.
// Link: https://www.programiz.com/dsa/heap-data-structure
void heap::percolateDown(int cPos){
    while(cPos <= stored/2){
        int indexLeft = 2 * cPos;
        int indexRight = 2 * cPos + 1;
        int s = cPos;
        if(indexLeft <= stored && data[indexLeft].key < data[s].key){
            s = indexLeft;
        }
        if(indexRight <= stored && data[indexRight].key < data[s].key){
            s = indexRight;
        }
        if(s != cPos){
            swap(data[cPos], data[s]);
            mapping.setPointer(data[cPos].id, &data[cPos]);
            mapping.setPointer(data[s].id, &data[s]);
            cPos = s;
        }
        else{
            break;
        }
    }
}

// Returns position of given node in heap array data. 
int heap::returnPosition(node *pn){
    int pos = pn - &data[0];
    return pos;
}

 // Checks if "percolate up" is needed at certain index.
 // Video (in python, but I implemented strategy for c++): https://www.youtube.com/watch?v=UFyTksTXFTA&t=2s
 bool heap::checkPercUp(int i){
    return (i > 1 && data[i].key < data[i / 2].key);
}

// Checks if "percolate down" is needed at certain index.
bool heap::checkPercDown(int i){
    int indexLeft = 2 * i;
    int indexRight = 2 * i + 1;
    if(indexLeft <= stored && data[indexLeft].key < data[i].key){
        return true;
    }
    if(indexRight <= stored && data[indexRight].key < data[i].key){
        return true;
    }
    return false;
}
