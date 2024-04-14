/*
 *  unit_tests.h
 *  Peter Morganelli pmorga01 and Brendan Roy broy02
 *  4/14/24
 *
 *  CS15 gerp
 *
 *  Testing file for gerp
 *  Specifically tests all functions in the processing.cpp file
 *  such as stripNonAlphaNum and traverseDirectory
 *
 */

#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stdexcept>

#include "hashtable.h"
#include "processing.h"
#include "DirNode.h"
#include "FSTree.h"

/********************************************************************\
*                           GERP TESTS!                              *
\********************************************************************/



void testStripNonAlphaNum(){
    string test1 = "@@@CAT@@@";
    string test2 = "$@@#^@$%#$&^%&*(^(*&()^cookies";
    string test3 = "walnut";
    string test4 = "Walnut!";
    string test5 = "!!!!!AND THEY WERE ROOMMATES!!!!";
    string test6 = "@$#toi@$@#$#let";
    string test7 = ")(#$)toilet@$@#$@#";
    string test8 = "@##!!#!@!#COMP-15!!!!!!!";

    string stripped1 = stripNonAlphaNum(test1);
    string stripped2 = stripNonAlphaNum(test2);
    string stripped3 = stripNonAlphaNum(test3);
    string stripped4 = stripNonAlphaNum(test4);
    string stripped5 = stripNonAlphaNum(test5);
    string stripped6 = stripNonAlphaNum(test6);
    string stripped7 = stripNonAlphaNum(test7);
    string stripped8 = stripNonAlphaNum(test8);

    assert(stripped1 == "CAT");
    assert(stripped2 == "cookies");
    assert(stripped3 == "walnut");
    assert(stripped4 == "Walnut");
    assert(stripped5 == "AND THEY WERE ROOMMATES");
    assert(stripped6 == "toi@$@#$#let");
    assert(stripped7 == "toilet");
    assert(stripped8 == "COMP-15");
}

void testDirectoryTraversal(){
    string directory = "test-dirs";
    // FSTree myTree(directory);
    // if(myTree.isEmpty()){
    //     cout << "hooray";
    // }
    traverseDirectory(directory);
}