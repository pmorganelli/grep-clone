/*
 *  hashtable.cpp
 *
 *  Peter Morganelli pmorga01 and Brendan Roy broy02
 * 
 *  4/13/24
 *
 *  CS15 gerp
 *
 *  Implementation of hashtable.h
*/

#include "hashtable.h"


/*
* name:      HashTable
* purpose:   a constructor to make a default HashTable
* arguments: none -- it is a constructor
* returns:   nothing
* effects:   n/a
*/
HashTable::HashTable(){
    size = 0;
    capacity = 350000;
    loadFactor = 0.7;
    table = new HashIndex[capacity];
}
/*
* name:      ~HashTable
* purpose:   a destructor for the hash table
* arguments: none
* returns:   nothing -- it is a destructor
* effects:   deletes the hash table
*/
HashTable::~HashTable(){
    delete [] table;
}

/*
* name:      getIndex
* purpose:   to get the index of the word in our hash table
* arguments: string with the word
* returns:   int that is the index that the word hashes to
* effects:   none
*/
int HashTable::getIndex(string word){
    string lowerWord; // get lowercase version of the word
    for (char c : word) lowerWord.push_back(tolower(c));
    size_t idx = hashFunction(lowerWord) % capacity;
    if (not table[idx].empty){ //get the next valid index (probe linearly -_-)
        while (not table[idx].empty and table[idx].word != lowerWord){
            idx = (idx + 1) % capacity;
        } 
    }
    return idx;
}


/*
* name:      add 
* purpose:   to add a given word to our hash table
* arguments: a string word to add, and two indexes to navigate our 2D vector
*            (think of them as rows and columns, where indexOne is the row
*            associated with a unique file, and indexTwo is the column
*            containing the line number it appears on)
* returns:   nothing
* effects:   adds a word to the hash table
*/
void HashTable::add(string word, int indexOne, int indexTwo){
    if ((double)size / (double)capacity > loadFactor)  rehash();
    string lowerWord;
    for (char c : word) lowerWord.push_back(tolower(c));
    int idx = getIndex(word); // get the index of the word
    if (table[idx].empty) size++; // increment size if needed
    bool hasWord = false;
    int versionNum;
    HashIndex *curr = &table[idx];
    curr->empty = false;
    curr->word = lowerWord;
    int currSize = curr->versions.size();
    for (int i = 0; i < currSize; i++){ // see which version to add to
        if (curr->versions.at(i) == word){
            hasWord = true;
            versionNum = i;
        }
    }
    bool hasLine = contains(indexOne, indexTwo, *curr);
    if (not hasWord) { // add new version of the word
        curr->versions.push_back(word);
        curr->instances.push_back(vector<Word>());
        curr->instances.back().push_back(Word(hasLine, indexOne, indexTwo));
    } else { // add to the back of existing version
        if (curr->instances.at(versionNum).back().index2 == indexTwo 
            and curr->instances.at(versionNum).back().index1 == indexOne)
            return;
        curr->instances.at(versionNum).push_back
                                      (Word(hasLine, indexOne, indexTwo));
    }  
}

/*
* name:      contains
* purpose:   to see if a word is already in our hash table
* arguments: two indexes for our 2D vector (see add() purpose for detailed
*            description) and our current HashIndex
* returns:   a boolean t/f whether or not the word is contained in the 
*            hash table
* effects:   none
*/
bool HashTable::contains(int idx, int idx2, HashIndex &curr){
    // check if any version of the word appears on the line we are adding
    for (size_t i = 0; i < curr.instances.size(); i++){
        if (curr.instances.at(i).size() > 0){
            int index1 = curr.instances.at(i).back().index1;
            int index2 = curr.instances.at(i).back().index2;
            if (idx == index1 and index2 == idx2) return true;
            
        }
    }
    return false;
}

/*
* name:      rehash
* purpose:   to expand the size of our hash table
* arguments: none
* returns:   none
* effects:   deletes the current hash table and allocates memory for a new
*            one with doubled capacity, and rehashes all of its elements
*/
void HashTable::rehash(){
    int newTableSize = capacity * 2;
    HashIndex *newTable = new HashIndex[newTableSize];
    size_t idx = 0;

    for (int i = 0; i < capacity; i++){ // rehash every nonempty index
        if (not table[i].empty){
            idx = hashFunction(table[i].word) % newTableSize;
        }
        while (not newTable[idx].empty) idx = (idx + 1) % newTableSize;
        newTable[idx] = table[i];
    }
    // set table to the new table and deallocate previously used memory
    delete [] table;
    table = newTable;
    capacity = newTableSize;
}

/*
* name:      searchSensitive
* purpose:   to search for a word in our hash table with case sensitivity
* arguments: a string word that we're looking for and the outfile to print to
* returns:   none
* effects:   prints to the given output file based on what was found
*/
void HashTable::searchSensitive(string word, ostream &outfile){
    string lowerWord; // get lowercase version of the word
    for (char c : word) lowerWord.push_back(tolower(c));
    int idx = getIndex(lowerWord);
    int versionNum = -1;
    for (size_t i = 0; i < table[idx].versions.size(); i++){
        if (word == table[idx].versions.at(i)){
            versionNum = i; // get the specific version's index
        }
    }
    if (versionNum == -1 or word == "") { // word doesn't exist
        outfile << word << " Not Found. Try with @insensitive or @i." << endl; 
        return;
    }
    if (table[idx].word == lowerWord) { // print all lines of the word
        for (size_t i = 0; i < table[idx].instances.at(versionNum).size(); i++){
            int index1 = table[idx].instances.at(versionNum).at(i).index1;
            int index2 = table[idx].instances.at(versionNum).at(i).index2;
            outfile << allLines.at(index1).first << ":" <<
                    allLines.at(index1).second.at(index2) << endl;
        }
    } 
}

/*
* name:      searchInsensitive
* purpose:   to search for a word in our hash table WITHOUT case sensitivity
* arguments: a string word to search for, and the output file to print to
* returns:   none
* effects:   prints to the given output file
*/
void HashTable::searchInsensitive(string word, ostream &ofile){
    string lowerWord;
    for (char c : word) lowerWord.push_back(tolower(c));
    int idx = getIndex(word);
    if (word == "" or table[idx].empty){ // word is not in the table
        ofile << word << " Not Found." << endl;
        return;
    }
    bool hasWord = false;
    if (table[idx].word == lowerWord) { // print out each version of the word
        hasWord = true;
        for (size_t i = 0; i < table[idx].instances.size(); i++){
            for (size_t j = 0; j < table[idx].instances.at(i).size(); j++){
                int idx1 = table[idx].instances.at(i).at(j).index1;
                int idx2 = table[idx].instances.at(i).at(j).index2;
                string path =  (allLines.at(idx1).first) + ":"; 
                if (not table[idx].instances.at(i).at(j).seen) {
                    ofile << path << allLines.at(idx1).second.at(idx2) << endl;
                }
            }
        }
    }
    if (not hasWord) ofile << word << " Not Found." << endl; // word not found
}

/*
* name:      addLine
* purpose:   to add an instance of line to our hash table
* arguments: a string word to add, the line number it occurs on, and its
*            full filepath which is needed for printing
* returns:   a pair of two integers used for our 2D vector
* effects:   adds to allLines (our 2D vector)
*/
pair<int, int>HashTable::addLine(string line, int lineNum, string filePath){
    bool hasFile = false;

    // add line number to file path 
    string newString = to_string(lineNum) + ": " +  line; 
    int versionNum = -1;
    // get the filepath that we will add to
    for (int i = allLines.size(); i > 0 and not hasFile; i--){
        if (allLines.at(i - 1).first == filePath){
            hasFile = true;
            versionNum = i - 1;
        }
    }
    if (hasFile){  // add line to back of filepath index
        allLines.at(versionNum).second.push_back(newString);
        return (pair<int, int>(versionNum, 
                allLines.at(versionNum).second.size() - 1));
    } else { // we have a new file. add new vector to allLines
        allLines.push_back(pair<string, vector<string>>());
        allLines.back().first = filePath;
        allLines.back().second.push_back(newString);
        return (pair<int, int>(allLines.size() - 1, 
                               allLines.back().second.size() - 1));
    }
}

/*
* name:      open_or_die
* purpose:   to open a given file
* arguments: a file stream address and the name of the file as a string
* returns:   none
* effects:   throws an error if the file fails to open
*/
template<typename streamtype>
void HashTable::open_or_die(streamtype &stream, string filename){
    stream.open(filename);
    if (not(stream.is_open())){
        string error = "Unable to open file " + filename;
        throw runtime_error(error);
    }
}