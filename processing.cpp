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
    // create tree then pass it into helper function
    FSTree d(directory);
    DirNode *root = d.getRoot();
    traverseDirectoryHelper(root);    
}

/*
* name:      traverseDirectoryHelper
* purpose:   to traverse the directory given an FSTree and output each file           
* arguments: a pointer to the root of the tree to traverse
* returns:   none; it is void
* effects:   prints out every file in given directory + subdirectory
*/
void traverseDirectoryHelper(DirNode *root){
    if(root->hasFiles()){ // print all files in the directory
        int numFilesCount = root->numFiles();
        for(int i = 0; i < numFilesCount; i++){
            cout << retrieveParents(root) << "/" << root->getFile(i) << endl;
        }
    }

    if(root->hasSubDir()){ // run traverseDirectoryHelper on each subdirectory
        for(int i = 0; i < root->numSubDirs(); i++){
            traverseDirectoryHelper(root->getSubDir(i));
        }
    }
}

/*
* name:      retrieveParents
* purpose:   get all the parents of a given subdirectory node
* arguments: pointer to a DirNode whose parents we want to return
* returns:   a string of all the DirNode's parents 
* effects:   none
*/
string retrieveParents(DirNode *root){
    if (root->getParent() != nullptr){
        return retrieveParents(root->getParent()) + "/" + root->getName();
    }
    else return root->getName();
}