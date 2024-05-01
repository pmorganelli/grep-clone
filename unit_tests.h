/*
 *  unit_tests.h
 *  Peter Morganelli pmorga01 and Brendan Roy broy02
 *  4/14/24
 *
 *  CS15 gerp
 *
 *  Unit testing file for gerp
 *
 *  Specifically tests all functions in the processing.cpp file
 *  such as stripNonAlphaNum and traverseDirectory. Was also used in the 
 *  beginning stages of part 2 to test functions individually. Many of these
 *  functions are now private, but we left the tests commented out to show what
 *  was tested.
 *  
 */

#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <vector>
#include <list>
#include <utility>

#include "hashtable.h"
#include "processing.h"
#include "DirNode.h"
#include "FSTree.h"
#include "gerp.h"

/********************************************************************\
*                           GERP TESTS!                              *
\********************************************************************/


//tests stripNonAlphaNum
//We decided it was best to test all of these in one function
//rather than splitting it up into 8 functions. If we were to run into a bug,
//we commented out certained assert statements to narrow
//down our debugging
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

//tests traverseDirectory for part 1
void testDirectoryTraversal(){
    string directory = "test-dirs";
    traverseDirectory(directory);
}

//tests adding to the hash table
void testAdd(){
    HashTable table;
    ofstream outfile;
    string peter = "Peter";
    int index1 = 1;
    int index2 = 1;
    //string line = "Peter once again has aced his chemistry exam";
    table.add(peter, index1, index2);
    table.searchInsensitive("PETER", outfile);                                
}

//test adding a word that has to be stripped of its nonalphanumeric chars first
void testAddWithStrippedString(){
    HashTable table;
    ofstream outfile;
    string word = "@!#comp?!@#@!";
    string strippedString = stripNonAlphaNum(word);
    string line = "comp 15 is so unfortunate";
    table.add(strippedString, 90, 1);
    table.searchInsensitive("comp", outfile);
}

// tests adding + size + rehash function (capacity was set to 10 initially)
void testAddManyElems(){
    ifstream infile("out.txt");
    string curr;
    HashTable table;
    int ct = 1;
    while (infile >> curr) {
        table.add(curr, ct, 1);
        ct++;
    }
  //  assert(table.getSize() == 25); <-- getSize was used previously
  //                                     when we were testing the size of table
}

// this tests the processFile() function, which is now private. We used this
// to ensure that we were reading everything in correctly with cout statements
// and search methods
void testProcessFile(){
    Gerp g;
    HashTable h;
    string inputFile = "out.txt";

    // g.processFile("cs15/gerp"); <-- This was used to test when processFile
    //                                 was a public member, commented out to
    //                                 show evidence of testing
    ofstream outfile("outputTest.txt");
    // g.table.searchInsensitive("naThan", outfile); <-- same thing here!


}

//tests searchSensitive
void testSearchSensitive(){
    Gerp g;
    HashTable h;
    string inputFile = "out.txt";

    // g.processFile(inputFile, "cs15/gerp"); <-- This was used to test when 
    //                                            processFile was a public
    //                                            member, commented out to
    //                                            show evidence of testing
    ofstream outfile("outputTest.txt");
    // g.table.searchSensitive("Nathan", outfile); <-- same thing here
}

//test searchInsensitive
void testSearchInsensitive(){
    Gerp g;
    HashTable h;
    string inputFile = "out.txt";
    // g.processFile(inputFile); <-- This was used to test when processFile
    //                                 was a public member, commented out to
    //                                 show evidence of testing
    ofstream outfile("outputTest.txt");
    // g.table.searchInsensitive("Peter", outfile); <-- same thing here
}