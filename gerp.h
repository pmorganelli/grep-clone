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


#ifndef _GERP_H_
#define _GERP_H_

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct Word{

};

struct Line{
    bool seen = false;
};

class Gerp{
    public:
        void run(string directory, string outputFile);
        

    private:
        template<typename streamtype>
        void open_or_die(streamtype &stream, string filename);
        void quit();
};


#endif