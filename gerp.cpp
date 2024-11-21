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
    open_or_die(outputFileStream, outputFile); // open output stream
    if (not indexDirectory(directory)) return;  // index the directory
    string query;
    string word;
    cout << "Query? ";
    while (cin >> query){ // continue accepting query
        if ((query == "@q") or (query == "@quit")){ // quit query
            cout << "Goodbye! Thank you and have a nice day." << endl;
            return;
        } else if (query == "@i" or query == "@insensitive"){
            cin >> word; // get word to search for
            string strippedWord = stripNonAlphaNum(word);
            table.searchInsensitive(strippedWord, outputFileStream);
        } else if (query == "@f"){ // switch output file
            cin >> word; // word functions as the name of the output file here
            outputFileStream.close(); // close and open the new file stream
            open_or_die(outputFileStream, word);
        } else {
            string strippedWord = stripNonAlphaNum(query);
            table.searchSensitive(strippedWord, outputFileStream);
        }
        cout << "Query? ";
    }
    cout << "Goodbye! Thank you and have a nice day." << endl;
}


/*
* name:      processFile
* purpose:   to read the inputted file and add the contents to hash table
* arguments: name of the file to be read
* returns:   nothing; it is void
* effects:   adds the lines to the big vector and each word to the hash table
*/
void Gerp::processFile(string filePath){
    ifstream infile;
    open_or_die(infile, filePath); // open the file
    int lineCount = 1; // this is the line number
    while (infile.peek() != -1){ // while the file has contents
        string line;
        getline(infile, line);
        istringstream lineStream(line);

        // this gets us the first and second index of the allLines vector
        pair<int, int> indices = table.addLine(line, lineCount, filePath);
        string curr;
        while (lineStream >> curr){ // read each word in the line
            curr = stripNonAlphaNum(curr);
            table.add(curr, indices.first, indices.second);            
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
* returns: bool saying if the directory exists or not
* effects:   
*/
bool Gerp::indexDirectory(string directory){
    try { // try to open make the directory with the given name
        FSTree tree(directory);
        DirNode *root = tree.getRoot();
        indexDirectoryHelper(root);
        return true;
    } catch (runtime_error){ // the directory name is invalid
        cerr << "Could not build index, reason:" << endl << "Directory \"" <<
                directory << "\" not found: could not build tree" << endl;
        return false;
    }
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
    if (root->hasSubDir()){ // traverse each subdirectory
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