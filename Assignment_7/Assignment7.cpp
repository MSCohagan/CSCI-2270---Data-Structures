#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "HashTable.hpp"
using namespace std;

//The constrcuctor should set the hashTable variable to be a dynamically allocated
//array of wordItem structs, of size hashTableSize, as well as set the hashTableSize
//member variable so that other functions can use it
HashTable::HashTable(int hashTableSize)
{
    //cout << "Hash Table constructor" << endl;
    this->hashTableSize = hashTableSize;
    hashTable = new wordItem*[hashTableSize];
    for(int i = 0; i < hashTableSize; i++)
    {
        hashTable[i] = NULL;
    }
    //cout << "Has Table constcuted" << endl;
}
//The deconstructor should free all the dynamic memory allocated by the table
HashTable::~HashTable()
{
    for(int i = 0; i < hashTableSize; i++)
    {
        wordItem* current = hashTable[i];
        while(current!=NULL)
        {
            wordItem* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] hashTable;
}

//The getHash funtion should return the hash of word using the DJB2 algorithm.
int HashTable::getHash(string word)
{
    /* PSUEDO CODE:
        int hash(string word):
        for each character c in word:
            hash = hash*33 + c
        hash = hash % hashTableSize
        if(hash < 0 ) hash += hashTableSize
        return hash;
    */
   //cout << "get hash" << endl;
   int hash = 5381;
   for(int i=0; i<word.length(); i++)
   {
       hash = hash*33 + int(word[i]);
   }
   hash = hash % hashTableSize;
   if(hash<0)
   {
       hash+= hashTableSize;
   }
   //cout << hash << endl;
   return hash;
}

//The searchTable function should search the table and return
//a pointer to the wordItem struct containing word, or NULL if the word
//doesn't exist in the table
wordItem* HashTable::searchTable(string word)
{
    //cout << "search table" << endl;
    wordItem* current;
    int i = getHash(word);
    current = hashTable[i];
    while(current != NULL)
    {
            if(current->word != word ){
                current = current->next;
            }
            else{
                return current;
            }
    }
    //cout << "table searched" << endl;
    return current;
   
}


//The getStopWords function should read stop words form ignoreWordFileName
//which should be formatted with exactly 50 words, one per line. It should
//store these words in the vecIgnoreWords vector, which is a member of HashTable
void HashTable::getStopWords(char* ignoreWordFileName)
{
    //cout << "get stop words" << endl;
    ifstream inFile;
    inFile.open(ignoreWordFileName);
    if(inFile.is_open())
    {
        for(int i = 0; i < 50; i++)
        {
            string info;
            inFile >> info;
            vecIgnoreWords[i] = info;
            //cout << vecIgnoreWords[i] << endl;
        }
    
    }
    else
    {
        cout << "Input file failed to open " << endl;
    }
    //cout << "got stop words" << endl;
    inFile.close();
}

// Check if word is in list of words to ignore
bool HashTable::isStopWord(string word)
{
    //cout << "is stop word" << endl;
    for(int i = 0; i < 50; i++)
    {
        if(vecIgnoreWords[i] == word)
        {
            return true;
        }
    }
    return false;
}

// The isInTable function should return whether the given word is in the table
bool HashTable::isInTable(string word)
{
    int i = getHash(word);
    //cout << "is in table?" << endl;
    wordItem* current = hashTable[i];
    while(current != NULL)
    {
        if(current->word != word )
        {
            current = current->next;
        }
        else if(current->word == word)
        {
            return true;
        }
    }
    //cout << "is in table." << endl;
    return false;
}

//The incrementCount function should add 1 to the count of the given word
void HashTable::incrementCount(string word)
{
    //cout << "increment count" << endl;
    wordItem* current = searchTable(word);
    if(current != NULL){
        current->count = current->count + 1; 
    }
    //cout << "count incremented" << endl;
}

//The addWord function should insert words in to the table with a count of 1.
//If the word collides with another that already exists in the table, add the new
//word to the end of the linked list chain
void HashTable::addWord(string word)
{
    //cout << "add word" << endl;
    int hashValue = getHash(word);
    if(hashTable[hashValue] == NULL)
    {
        hashTable[hashValue] = new wordItem;
        //cout << "if statement" << endl;
        hashTable[hashValue]->word = word;
        //cout << hashTable[hashValue]->word << endl;
        hashTable[hashValue]->count = 1;
        //cout << hashTable[hashValue]->count << endl;
        hashTable[hashValue]->next = NULL;
    }
    else
    {
        //cout << "else statement" << endl;
        wordItem* current = hashTable[hashValue];
        while(current->next != NULL)
        {
            //cout << "in the while loop " << endl;
            current = current->next;
            //cout << current->word << endl;
        }
        wordItem* newWord = new wordItem;
        current->next = newWord;
        newWord->word = word;
        newWord->count = 1;
        newWord->next = NULL;
    }
    //cout << "word added" << endl;
}

//The getTotalNumberNonStopWords function should return the total number
//of non-stop words in the entire tree, counting duplicates.
int HashTable::getTotalNumberNonStopWords()
{
    int total = 0;
    for(int i = 0; i < hashTableSize; i++)
    {
        wordItem* current = hashTable[i];
        while(current != NULL)
        {
             total = total + current->count;
             current = current->next;
        }
    }
    return total;
}

void printTopNHelper(wordItem** hashTable, vector<wordItem*> &sortedArray, int size)
{
    for(int i = 0; i < size; i++)
    {
        //cout << "For loop" << endl;
        wordItem* current = hashTable[i];
        while(current!= NULL)
        {
            //cout << "while loop" << endl;
            sortedArray.push_back(current);
            current = current->next;
        }
    }
    //Selection Sort
    for(int i = 0; i < sortedArray.size()-1; i++){
        int currentMax = i;
        for(int j = i + 1; j < sortedArray.size(); j++){
            if(sortedArray[currentMax]->count < sortedArray[j]->count){
                currentMax = j;
            }
        }
        //swap(sortedArray[i], sortedArray[currentMax]);
        wordItem* tmp = sortedArray[i];
        sortedArray[i] = sortedArray[currentMax];
        sortedArray[currentMax] = tmp;
    }
}


//The printTopN function should print the top n most common words in the table
void HashTable::printTopN(int n)
{
    //cout << "printTopN" << endl;
    int size = hashTableSize;
    //cout << size << endl;
    vector<wordItem*>sortedArray;
    //cout << "sortedArray created" << endl;
    printTopNHelper(hashTable, sortedArray, size);
    for(int i = 0; i<n; i++)
    {
        cout << sortedArray[i]->count << " - " << sortedArray[i]->word << endl;
    }

}

//The printTopN function should print the top n most common words in the table
// void HashTable::printTopN(int n)
// {
//    //create an array of size n
//    wordItem* newArray[n];
//    for(int i = 0; i < n; i++)
//    {
//        wordItem* current = hashTable[i];
//        while(current != NULL)
//        {
//            for(int j = 0; j < n; j++)
//            {
//                if (newArray[j] == NULL || newArray[j]->count < current->count)
//                {
//                    for(int k = j+1; k < n-1; k++)
//                    {
//                        newArray[k+1] = newArray[k];
//                    }
//                    newArray[j] = current;
//                    break;
//                }
//            }
//            current = current->next; 
//            /*if(current->count > newArray[n-1])
//            {
               
//                newArray[i] = current;
//            }
//            */
//        }
//    }
//     for(int i = 0; i<n; i++)
//     {
//         cout << newArray[i]->count << " - " << newArray[i]->word << endl;
//     }
// }

//The getNumUniqueWords function should return the number of words in the table
//not counting duplicates of a word. This is NOT supposed to count the number
//of words that only appear once in the text
int HashTable::getNumUniqueWords()
{
    int total = 0;
    for(int i = 0; i < hashTableSize; i++)
    {
        wordItem* current = hashTable[i];
        while(current != NULL)
        {
            total+=1;
            current = current->next;
        }
    }
    return total;
}

//The getNumCollisions function should return the number of sollisions in the table
int HashTable::getNumCollisions()
{
    int total = 0;
    for(int i = 0; i < hashTableSize; i++)
    {
        wordItem* current = hashTable[i];
        while(current != NULL)
        {
            if(current->next != NULL || current == NULL)
            {
                total += 1;
            }
            current = current->next;
        }
    }
    return total;
}

//Main function, be sure to include in separate file when turning in
int main(int argc, char* argv[])
{
    HashTable hashTable(stoi(argv[4]));
    ifstream inFile;
    inFile.open(argv[2]);
    hashTable.getStopWords(argv[3]);
    if(inFile.is_open())
    {
        string currentLine;
        while(getline(inFile,currentLine))
        {
            stringstream ss(currentLine);
            string word;
            while(getline(ss,word,' '))
            {
                if(word != "" && hashTable.isStopWord(word) == false && hashTable.isInTable(word) == false)
                {
                    hashTable.addWord(word);
                }
                else if(word != "" && hashTable.isStopWord(word) == false)
                {
                    hashTable.incrementCount(word);
                }
            }
        }
        hashTable.printTopN(stoi(argv[1]));
        cout << "#" << endl;
        cout << "Number of collisions: " << hashTable.getNumCollisions() << endl;
        cout << "#" << endl;
        cout << "Unique non-stop words: " << hashTable.getNumUniqueWords() << endl;
        cout << "#" << endl;
        cout << "Total non-stop words: " << hashTable.getTotalNumberNonStopWords() << endl;
    }
    else{
        cout << "Input file failed to open " << endl;
    }
    inFile.close();
}