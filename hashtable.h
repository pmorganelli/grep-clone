/*
 *  hashtable.h
 *
 *  Peter Morganelli pmorga01 and Brendan Roy broy02
 * 
 *  4/13/24
 *
 *  CS15 gerp
 *
 *  This file is the interface for our HashTable class, including
 *  methods to add, search, and rehash our table. This class is an integral
 *  part of how we store data for Gerp because constant access time is
 *  important as the size of the data increases.
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
    struct HashIndex;
    struct Word;
    
    public:
        HashTable();
        ~HashTable();
        pair<int, int>addLine(string line, int lineNum, string filePath);
        void add(string word, int indexOne, int indexTw);
        void searchSensitive(string word, ostream &ofile);
        void searchInsensitive(string word, ostream &ofile);
        
    private: 
        template<typename streamtype>
        void open_or_die(streamtype &stream, string filename);

        bool contains(int idx, int idx2, HashIndex &curr);
        void rehash();
        int getIndex(string word);
        HashIndex *table;
        hash<string> hashFunction;
        vector<pair<string, vector<string>>> allLines;
        int capacity;
        int size;
        double loadFactor = 0.7;

        struct HashIndex {
            vector<string> versions;
            vector<vector<Word>> instances;
            bool empty;
            string word;
            HashIndex(){
                empty = true;
                word = "";
            }
        };
        
        struct Word {
            int index1;
            int index2; 
            bool seen;
            Word (bool toPrint, int indexOne, int indexTwo){
                seen = toPrint;
                index1 = indexOne;
                index2 = indexTwo;
            }
        };
};

#endif