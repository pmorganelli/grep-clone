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

#include <sstream>
using namespace std;

/*
* name:      run
* purpose:   the main function to execute the gerp program, including the
*            query loop and searching sensitively/insensitively
* arguments: a string that is the name of the directory given by the user, and 
*            a string that is the name of the outputfile given by the user
* returns:   nothing
* effects:   calls several other functions such as open_or_die, indexDirectory,
*            stripNonAlphaNum, searchInsensitive, and searchSensitive
*/
void Gerp::run(string directory, string outputFile){
    ofstream outputFileStream;
    open_or_die(outputFileStream, outputFile);
    indexDirectory(directory);
    string query;
    string word;
    cout << "Query? ";
    while (cin >> query){
        if ((query == "@q") or (query == "@quit")){
            cout << "Goodbye! Thank you and have a nice day." << endl;
            return;
        }
        else if (query == "@i" or query == "@insensitive"){
            cin >> word;
            string strippedWord = stripNonAlphaNum(word);
            table.searchInsensitive(strippedWord, outputFileStream);
        }
        else if (query == "@f"){
            cin >> word; //word functions as the name of the output file here
            string strippedWord = stripNonAlphaNum(word);
            
            //close current output stream and open a new one
            outputFileStream.close();
            open_or_die(outputFileStream, strippedWord);
        }
        else {
            string strippedWord = stripNonAlphaNum(query);
            table.searchSensitive(strippedWord, outputFileStream);

        }
        cout << "Query? ";
    }
    cout << "Goodbye! Thank you and have a nice day." << endl;
}

void Gerp::processFile(string filePath){
    ifstream infile;
    open_or_die(infile, filePath);

    int lineCount = 1;
    while (infile.peek() != -1){
        string line;
        getline(infile, line);
        istringstream lineStream(line);
        pair<int, int> s = table.addLine(line, lineCount, filePath);

        string curr;
        while (lineStream >> curr){
            curr = stripNonAlphaNum(curr);
            table.add(curr, s.first, s.second);            
        }
        lineCount++;
    }
}


/*
* name:      open_or_die
* purpose:   to open an file stream or throw an error
* arguments: a flexible stream (becuase of the templating streamtype) and 
*            the name of the file as a string
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
* name: indexDirectory      
* purpose: to take the name of a directory and input contents into the HashTable
* arguments: string of the name of the directory to index
* returns: nothing; is void
* effects:   
*/
void Gerp::indexDirectory(string directory){
    FSTree tree(directory);
    DirNode *root = tree.getRoot();
    indexDirectoryHelper(root);
}


/*
* name:      indexDirectoryHelper
* purpose:   a helper function for indexDirectory that recursively deals with
*            subdirectories and files inside of a root (the original directory)
* arguments: a pointer to a DirNode called root that is the root of the FSTree
* returns:   nothing
* effects:   uses DirNode methods to traverse through subdirectories 
*/
void Gerp::indexDirectoryHelper(DirNode *root){
    if (root->hasFiles()){ // print all files in the directory
        int numFilesCount = root->numFiles();
        for(int i = 0; i < numFilesCount; i++){
            string filePath = retrieveParents(root) + "/" 
                              + root->getFile(i);
            
            processFile(filePath);
        }
    }
    if (root->hasSubDir()){
        for(int i = 0; i < root->numSubDirs(); i++){
            indexDirectoryHelper(root->getSubDir(i));
        }
    }
}

/*
* name:      retrieveParents
* purpose:   to get the name of the root's parent node
* arguments: a pointer to a DirNode root
* returns:   a string that is the name of the root's parent
* effects:   none
*/
string Gerp::retrieveParents(DirNode *root){
    if (root->getParent() != nullptr){
        return retrieveParents(root->getParent()) + "/" + root->getName();
    }
    else return root->getName();
}

/*
* name:      stripNonAlphaNum
* purpose:   to remove all trailing and leading non-alphanumeric chars from a 
*            string
* arguments: a string that will be stripped
* returns:   the inputted string without any trailing or leading 
*            non-alphanumeric chars in it
* effects:   trims a string using erase and pop_back()
*/
string Gerp::stripNonAlphaNum(string input){
    //remove all LEADING nonalphanumeric chars in the front
    while ((input.length() > 0) and (not isalnum(input.at(0)))){
        input.erase(0, 1); //replicating pop_front() without any shifting
    }

    //remove all TRAILING nonalphanumeric chars in the back
    int trailing = input.length() - 1;
    while ((trailing > 0) and (not isalnum(input.at(trailing)))){
        input.pop_back(); //remove the last char and iterate
        trailing--;
    }
    return input;
}