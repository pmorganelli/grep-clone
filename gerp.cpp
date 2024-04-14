/*
 *  gerp.cpp
 *
 *  Peter Morganelli pmorga01 and Brendan Roy broy02
 * 
 *  4/13/24
 *
 *  CS15 gerp
 *
 *  implementation file for gerp, the main searching program
*/

#include "gerp.h"

void Gerp::run(string directory, string outputFile){
    ofstream outputStream = open_or_die_output(outputFile);
}


/*
* name:      open_or_die_output
* purpose:   to open an output file and return it as a stream
* arguments: the name of the file as a string
* returns:   the output stream
* effects:   throws an error if the file fails to open
*/
ofstream Gerp::open_or_die_output(string filename){
    ofstream outputStream(filename);
    if (not(outputStream.is_open())){
        string error = "Unable to open file " + filename;
        throw runtime_error(error);
    }
    return outputStream;
}