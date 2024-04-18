/*
 *  hashtable.cpp
 *
 *  Peter Morganelli pmorga01 and Brendan Roy broy02
 * 
 *  4/13/24
 *
 *  CS15 gerp
 *
 *  implementation files for hashtable.h
*/

#include "hashtable.h"

struct Pair;


HashTable::HashTable(){

}

HashTable::~HashTable(){
    
}


void HashTable::add(string word, int lineNumber, string *linePointer){
    if ((double)size / (double)capacity > loadFactor)  rehash();
    string lowerWord;
    for (char c : word) lowerWord.push_back(tolower(c));
    int idx = hash_function(lowerWord) % capacity;
    if (not table[idx].empty){ // get the next valid index (probe linearly -_-)
        while (not table[idx].empty) idx = (idx + 3) % capacity;
    }
    bool hasWord = false;
    int versionNum;
    HashIndex curr = table[idx];
    curr.empty = false;
    curr.word = lowerWord;
    for (int i = 0; i < curr.versions.size(); i++){
        if (*(curr.versions.at(i).front().second) == word){
            hasWord = true;
            versionNum = i;
        }
    }
    if (not hasWord) {
        list<pair<int, string *>> newList;
        newList.push_back(pair<int, string*>(-1, &word));
        newList.push_back(pair<int, string*>(lineNumber, linePointer));
        curr.versions.push_back(newList);
    } else {
        curr.versions.at(versionNum).push_back(pair<int, string*>(lineNumber, linePointer));
    }
    size++;
}

void HashTable::remove(){

}

void HashTable::rehash(){
    int newTableSize = capacity * 2;
    HashIndex *newTable = new HashIndex[newTableSize];

    int idx = 0;
    for (int i = 0; i < capacity; i++){
        if (not table[i].empty){
            idx = hash_function(table[i].word) % newTableSize;
        } else {
            while (not newTable[idx].empty){
                idx = (idx + 3) % newTableSize;
            }
            newTable[idx] = table[i];
        }
    }
    delete table;
    table = newTable;
    capacity = newTableSize;
}

list<pair<int, string*>> *HashTable::searchSensitive(string word, ofstream &outfile){
    string lowerWord;
    for (char c : word) lowerWord.push_back(tolower(c));
    int idx = hash_function(lowerWord) % capacity;

    if (table[idx].word != word){
        while (not (table[idx].empty or table[idx].removed) 
               and (table[idx].word != word)) {
            idx = (idx + 3) % capacity;            
        }
    }

    if (table[idx].word == word) {
        for (int i = 0; i < table[idx].versions.size(); i++){
            if (*(table[idx].versions.at(i).front().second) == word){
                return &(table[idx].versions.at(i));
            }
        }
    }
    cout << word << "Not Found. Try with @insensitive or @i." << endl;
    return nullptr;
}

vector<list<pair<int, string*>>> *HashTable::searchInsensitive(string word, 
                                                            ofstream &outfile){
    string lowerWord;
    for (char c : word) lowerWord.push_back(tolower(c));
    int idx = hash_function(lowerWord) % capacity;

    if (table[idx].word != word){
        while (not (table[idx].empty or table[idx].removed) 
               and (table[idx].word != word)) {
            idx = (idx + 3) % capacity;            
        }
    }

    if (table[idx].word == word) {
        return &table[idx].versions;
    }
    cout << word << "Not Found. Try with @insensitive or @i." << endl;
    return nullptr;
}

template<typename streamtype>
void HashTable::open_or_die(streamtype &stream, string filename){
    (void) stream;
    (void) filename;
}