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
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#include <fstream>
using namespace std;

struct Word{

};

class HashTable{
    public:
        HashTable();
        ~HashTable();

        void run(string directory, string outputFile);
        ofstream open_or_die_output(string filename);
        //inset function into vector
        //float load factor
        //find
        //expand
        //add, etc

    private:


};

#endif