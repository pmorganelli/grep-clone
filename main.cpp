/*
 *  main.cpp
 *
 *  Peter Morganelli pmorga01 and Brendan Roy broy02
 * 
 *  4/13/24
 *
 *  CS15 gerp
 *
 *  main.cpp/driver file for gerp
 *  which is similar to the Unix "grep" program that searches through
 *  different directories and files to find instances of a given query
 *
*/

#include <string>
#include <iostream>

#include "hashtable.h"
#include "processing.h"
#include "gerp.h"
using namespace std;


int main(int argc, char *argv[]){
    if(not (argc == 3)){
        std::cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        return EXIT_FAILURE;
    }

    Gerp g;
    g.run(argv[1], argv[2]);
    return 0;
}