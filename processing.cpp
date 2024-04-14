/*
 *  processing.cpp
 *
 *  Peter Morganelli pmorga01 and Brendan Roy broy02
 * 
 *  4/13/24
 *
 *  CS15 gerp
 *
 *  implementation files for processing.h
*/

#include "processing.h"
#include "DirNode.h"
#include "FSTree.h"

#include <iostream>

/*
* name:      stripNonAlphaNum
* purpose:   to remove all trailing and leading non-alphanumeric chars from a 
*            string
* arguments: a string that will be stripped
* returns:   the inputted string without any trailing or leading 
*            non-alphanumeric chars in it
* effects:   trims a string using erase and pop_back()
*/
string stripNonAlphaNum(string input){
    //remove all LEADING nonalphanumeric chars in the front
	while((input.length() > 0) and (not isalnum(input.at(0)))){
		input.erase(0, 1); //replicating pop_front() without any shifting
	}

    //remove all TRAILING nonalphanumeric chars in the back
	int trailing = input.length() - 1;
	while((trailing > 0) and (not isalnum(input.at(trailing)))){
		input.pop_back(); //remove the last char and iterate
		trailing--;
	}
	return input;
}


/*
* name:      traverseDirectory
* purpose:   to print out all the files within the directory and
*            the directory's sub-directories
* arguments: the name of the desired directory as a string
* returns:   none
* effects:   prints all the file paths to cout
*/
void traverseDirectory(string directory){
    FSTree d(directory);
    DirNode *root = d.getRoot();
    if(d.isEmpty()){
        cout << "hi";
        return;
    }

    //TODO: modularize code below
    if(root->hasFiles()){
        int numFilesCount = root->numFiles();
        for(int i = 0; i < numFilesCount; i++){
            cout << directory << "/" << root->getFile(i) << endl;
        }
    }
    if(root->hasSubDir()){
        int subDirsCount = root->numSubDirs();
        for(int i = 0; i < subDirsCount; i++){
            traverseDirectory(root->getSubDir(i)->getName());
            // DirNode *newNode = root->getSubDir(i);
            // root->setParent(newNode);
            // DirNode *newRoot = d.getRoot();
        }
    } else {
        return;
    }

    // cout << directory << "/";

}

void traverseDirectoryHelper(){
    
}

