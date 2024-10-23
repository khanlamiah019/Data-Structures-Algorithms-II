/* Lamiah Khan DSA II, 10/10/2024
 Credits: hash.cpp was implemented from Project 1. 
 Any resources used will be linked to within the document.*/

#include "hash.h"

using namespace std;

//initializing hash table: capacity shows size of table is set to next prime number greater/equal to size.
//Filled tracks slots filled in hash table, data shows a vector of hashItem objects initialized with size.
hashTable::hashTable(int size){
    capacity = getPrime(size);
    filled = 0;
    data.assign(capacity,hashItem());
}

//Inserting keys into  Hash Table.
int hashTable::insert(const string &key, void *pv){
    //if key is already in table, returns 1
    if(contains(key)){
        return 1;
    }
    //if table is more than half full, it triggers rehash (resizes +distributes)
    if(filled >= capacity/2){
        if(!rehash()){
            return 2;
        }
    }
    //Linear probing: https://www.tutorialspoint.com/cplusplus-program-to-implement-hash-tables-with-linear-probing
    //hash function computes index i, if slot at i is occupied function uses linear probing until empty slot is found.
    int i = hash(key);
    while(data[i].isOccupied){
        i = (i+1)%capacity;
    }
    //When empty slot is found, key is stored in slot, and isOccupied = true, isDeleted = false, function returns 0.
    data[i].key = key;
    data[i].isOccupied = true;
    data[i].isDeleted = false;
    data[i].pv = pv;
    filled++;
    return 0;
}

//Function checks if key exists in the hash table. Calls findPos to find position of key.
bool hashTable::contains(const string &key){
    if(findPos(key)==-1){
        return false;
    }else{
        return true;
    }
}

//Hash Function from DSA Analysis in C++ (Fourth Edition): page 195
//link: https://www.uoitc.edu.iq/images/documents/informatics-institute/Competitive_exam/DataStructures.pdf
int hashTable::hash(const string &key){
    int hashVal = 0;
    for(int i=0; i<key.length(); i++){
        hashVal = 53 * hashVal + key[i];
    }
    hashVal %= capacity;
    if(hashVal < 0){
        hashVal += capacity;
    }
    return hashVal;
}

//Function to research to key's position in hash table.
// Link: https://stackoverflow.com/questions/16430857/hash-function-for-hash-table-with-strings-and-integers-as-keys
int hashTable::findPos(const string &key){
    int position = hash(key);
    if(!data[position].isOccupied){
        return -1;
    }
    //Linear probing: https://www.tutorialspoint.com/cplusplus-program-to-implement-hash-tables-with-linear-probing
    while(data.at(position).isOccupied){
        if(data.at(position).key.compare(key)==0 && !data[position].isDeleted){
            return position;
        }
        position++;
        position%=capacity;
    }
    return -1;
}
//Rehash function outputing a success report
//Process of inserting occipied slots in old hash to new hash table = Reduces collisions!
//code: https://stackoverflow.com/questions/65063117/hash-table-adding-a-rehash-to-resize-method
bool hashTable::rehash(){
    vector<hashItem> prevData = data;
    capacity = getPrime(capacity);
    data.clear();
    data.resize(capacity);
    if(!capacity){
        capacity = data.size();
        return false;
    }else{
        for(int i = 0; i < capacity; i++){
            data[i].isOccupied = false;
        }
        for(int j = 0; j < prevData.size(); j++){
            if(prevData[j].isOccupied && !prevData[j].isDeleted){
                insert(prevData[j].key, prevData[j].pv);
            }
        }
        prevData.clear();
    }
    return true;
}

// Finding + Returning the next largest prime number
unsigned int hashTable::getPrime(int size){
    static vector<unsigned int> primeNum = {49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469};
    for(int i = 0; i < primeNum.size(); i++){
        if(primeNum[i] > size){
            return primeNum[i];
        }
    }
    return 0;
}
//Fixed from Program 1 comments
//Get pointer associated with specified key
//Link: https://users.rust-lang.org/t/function-pointers-in-a-hashmap/6530
void *hashTable::getPointer(const std::string &key, bool *b){
    int i = findPos(key);
    if(i != -1){
        *b = true;
        return data[i].pv;
    }
    *b = false;
    return NULL;
}
//Set pointer associated with specified key
int hashTable::setPointer(const std::string &key, void *pv){
    int i = findPos(key);
    if(i == -1){
        return 1;
    }
    data[i].pv = pv;
    return 0;
}
//Delete item with specified key
bool hashTable::remove(const std::string &key){
    int i = findPos(key);
    if(i == -1){
        return false;
    }
    data[i].isDeleted = true;
    return true;
}
