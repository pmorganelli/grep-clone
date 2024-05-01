/*
 *  gerp.h
 *
 *  Peter Morganelli pmorga01 and Brendan Roy broy02
 * 
 *  4/13/24
 *
 *  CS15 gerp
 *
 *  The interface file for gerp, the main searching program!
 *  Gerp uses a query loop that enables the user to search for words in the
 *  given directory's files both case sensitively and insensitively. The word's
 *  file path, line number, and entire line are then printed to an output file 
 *  of the provided name. All queries are stripped of their non-alphanumeric 
 *  characters so that only the word itself is searched for. Gerp uses a hash
 *  table, so it has near-instant access time to the file lines it searches 
 *  for.
*/


#ifndef _GERP_H_
#define _GERP_H_

#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>

#include "hashtable.h"
#include "DirNode.h"
#include "FSTree.h"

using namespace std;

class Gerp{
    public:
        void run(string directory, string outputFile);
        
    private:
        HashTable table;
        void indexDirectory(string directory);
        void processFile(string filePath);
        void indexDirectoryHelper(DirNode *root);
        string stripNonAlphaNum(string input);
        string retrieveParents(DirNode *root);

        template<typename streamtype>
        void open_or_die(streamtype &stream, string filename);

};


#endif