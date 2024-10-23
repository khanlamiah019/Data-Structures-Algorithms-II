/* Lamiah Khan DSA II, 10/10/2024
 Credits: hash.cpp was implemented from Project 1. 
 Any resources used will be linked to within the document.*/


#ifndef _HEAP_H
#define _HEAP_H

#include "hash.h"
#include <string>
#include <vector>

// The following was used for the heap function (which was outlined in the instructions), and then editted. 
//https://www.geeksforgeeks.org/cpp-stl-heap/
//https://github.com/alyssaq/heap/blob/master/heap.h
class heap {
    // heap - The constructor allocates space for the nodes of the heap
    // and the mapping (hash table) based on the specified capacity
    public:
    // Allocates space for nodes and maps the hash table based on capacity. 
    heap(int capacity = 0);

    // Inserts a new node into the binary heap.
    // Returns:
    // 0 on success.
    // 1 if the heap is full.
    // 2 if a node with the given id already exists (but the heap
    // is not filled to capacity)

    int insert(const std::string &id, int key, void *pv = NULL);

    // Removes and returns the item with the lowest key in the heap.
    // Returns:
    // 0 on success.
    // 1 if the heap is empty.
    // ptrId is a pointer to a string & it stores the node ID w/ smallest key in the heap.
    // ptrKey is an optional pointer to an integer where the key of the node w/ the smallest key can be stored.
    int deleteMin(std::string *ptrId, int *ptrKey = NULL, void *ppData = NULL);

    // setKey - set the key of the specified node to the specified value
    // Sets the node's key to the given value.
    // Returns:
    // 0 on success.
    // 1 if the node does not exist.
    int setKey(const std::string &id, int key);

    // Deletes an item with a specified id from the heap.
    // Returns:
    // 0 on success.
    // 1 if the node does not exist. 
    int remove(const std::string id, int *key, void *ppData = NULL);

    private:

    // nested node class given
    class node{
    public:
    // The node id.
        std::string id;
    // The node key.
        int key;
    // A pointer to the actual data.
        void *pData; 
    };
    // Current capacity of heap.
    int capacity;
    //# of occupied items in the hash table.
    int stored; 
    //Binary heap.
    std::vector<node> data; 
    //Maps ids to node pointers.
    hashTable mapping; 

//Helpful Source: https://courses.cs.washington.edu/courses/cse326/06au/lectures/lect05.pdf
    // Swaps newly inserted item with parent until heap order is restored.
    void percolateUp(int cPos);
    // Swaps node with smaller of its two children until the heap order is restored.
    void percolateDown(int cPos);
    // Returns position of a given node.
    int returnPosition(node *pn);
    // Checks if "percolate up" is needed at certain index.
    bool checkPercUp(int i);
    // Checks if "percolate down" is needed at certain index.
    bool checkPercDown(int i);
};
#endif //_HEAP_H
