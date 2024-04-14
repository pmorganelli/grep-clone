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
using namespace std;


int main(int argc, char *argv[]){
    if(not (argc == 2)){
        std::cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        return EXIT_FAILURE;
    }

    (void) argc;
    (void) argv;

    HashTable h;
    h.run(argv[1], argv[2]);
    
    return 0;
}



// /*
// * name:      open_or_die_input
// * purpose:   to open a given input file
// * arguments: the name of the file as a string
// * returns:   none
// * effects:   throws an error if the file fails to open or if the input file
// *            is empty
// */
// ifstream open_or_die_input(string filename){
//     ifstream inputStream(filename);
//     if (not(inputStream.is_open())){
//         string error = "Unable to open file " + filename;
//         throw runtime_error(error);
//     }

//     char nextChar = inputStream.peek();
//     //check if the file is empty
//     if (nextChar == EOF) {
//         cout << filename + " is empty and cannot be compressed." << endl;
//         exit(EXIT_FAILURE);
//     }
//     return inputStream;
// }