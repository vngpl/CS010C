#include "HashTable.h"
#include "WordEntry.h"

HashTable::HashTable (int s) : size(s) {
	hashTable = new list<WordEntry>[size];
}

/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
/////////////////////////// from ChatGPT /////////////////////////// 
int HashTable::computeHash(const string &s) const {
	int wordHashIndex = 0;
	// iterate through characters in string
    for (const char& ch : s) {
		// add character's integer value to hash value
        wordHashIndex += ch;
    }
	// return remainder of value using size of hash table
    return wordHashIndex % size;
}
////////////////////////////////////////////////////////////////////


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &s, int score) {
	// get hash index
	int wordHashIndex = computeHash(s);

	// loop through word entrys at the index
	for (WordEntry& entry : hashTable[wordHashIndex]) {
		// if the word in the entry exists, add an appearance and return
        if (entry.getWord() == s) {
            entry.addNewAppearance(score);
            return;
        }
    }
    // if word not found, pushes back new word entry to list at the index
    hashTable[wordHashIndex].push_back(WordEntry(s, score));
}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/
double HashTable::getAverage(const string &s) const {
	int wordHashIndex = computeHash(s);

	// loop through entrys at the index
	for (const WordEntry& entry : hashTable[wordHashIndex]) {
		// if the word is found, return its average
		if (entry.getWord() == s) {
			return entry.getAverage();
		}
	}

	// word is not found at index, return 2.0
  	return 2.0;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) const {
	int wordHashIndex = computeHash(s);
	
	// loop through entrys at index
	for (const WordEntry& entry : hashTable[wordHashIndex]) {
		// if word found, return true
		if (entry.getWord() == s) {
			return true;
		}
	}

	// word not found, return false
	return false;
}