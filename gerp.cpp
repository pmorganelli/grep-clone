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
    Gerp g;
    ofstream outputStream;
    g.open_or_die(outputStream, outputFile);
    
    string query;
    cout << "Query? ";
    while((cin >> query) and ((query != "@q") or (query != "@quit"))){
        if(query.substr(0, 2) == "@i" or query.substr(0, 2) == "@insensitive"){
            //handle these cases
            cout << "bug" << endl;
        }
        if(query.substr(0, 2) == "@f"){
            //handle new output file
            cout << "hello man" << endl;
        }



    }
    g.quit();
}


/*
* name:      open_or_die
* purpose:   to open an output file and return it as a stream
* arguments: the name of the file as a string
* returns:   the output stream
* effects:   throws an error if the file fails to open
*/
template<typename streamtype>
void Gerp::open_or_die(streamtype &stream, string filename){
    stream.open(filename);
    if (not(stream.is_open())){
        string error = "Unable to open file " + filename;
        throw runtime_error(error);
    }
}

/*
* name:      open_or_die
* purpose:   to open an output file and return it as a stream
* arguments: the name of the file as a string
* returns:   the output stream
* effects:   throws an error if the file fails to open
*/
void Gerp::quit(){
    cout << "Goodbye! Thank you and have a nice day." << endl;
}