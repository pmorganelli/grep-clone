/*
 *  gerp.h
 *
 *  Peter Morganelli pmorga01 and Brendan Roy broy02
 * 
 *  4/13/24
 *
 *  CS15 gerp
 *
 *  interface file for gerp, the main searching program
*/


#ifndef GERP_H_
#define GERP_H_

#include <string>
#include <fstream>

using namespace std;

class Gerp{
    public:
        void run(string directory, string outputFile);
        ofstream open_or_die_output(string filename);

    private:
};


#endif