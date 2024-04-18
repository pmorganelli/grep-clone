/*
 *  processing.h
 *
 *  Peter Morganelli pmorga01 and Brendan Roy broy02
 * 
 *  4/13/24
 *
 *  CS15 gerp
 *
 *  interface file for part 1 of gerp, includes two functions: stripNonAlphaNum
 *  which takes in a string as input and returns that string without any
 *  non-alphanumeric numbers in it. Also includes traverseDirectory, which
 *  utilizes functions from the DirNode class and enters the directory that
 *  is given as and input string.
*/

#ifndef __PROCESSING_H
#define __PROCESSING_H


#include <string>
#include <cctype>
#include "DirNode.h"
#include "FSTree.h"
#include <iostream>
using namespace std;

string stripNonAlphaNum(string input);
void traverseDirectory(string directory);


void traverseDirectoryHelper(DirNode *root);
string retrieveParents(DirNode *root);
#endif 