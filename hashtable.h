/*
 *  hashtable.h
 *
 *  Peter Morganelli pmorga01 and Brendan Roy broy02
 * 
 *  4/13/24
 *
 *  CS15 gerp
 *
 *  
 *
*/
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <utility>
#include <functional>

using namespace std;



class HashTable{

    public:
        HashTable();
        ~HashTable();

        void add(string word, int lineNumber, string *linePointer);
        void remove();
        list<pair<int, string*>> *searchSensitive(string word, ofstream &outfile);
        vector<list<pair<int, string*>>> *searchInsensitive(string word, ofstream &outfile);
        



    private:

        void rehash();
        template<typename streamtype>
        void open_or_die(streamtype &stream, string filename);
        

        struct HashIndex {
            vector<list<pair<int, string *>>> versions;
            bool removed;
            bool empty;
            string word;
        };
        
        hash<string> hash_function;
        int size;
        int capacity;
        float loadFactor = 0.7;
        HashIndex *table;

};

#endif