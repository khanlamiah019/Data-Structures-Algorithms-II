/* Lamiah Khan DSA II, 09/15/2024
 Program uses a hash table class to read a "dictionary" and spell check a "document.
 Content from hash.h file and makefile were kept the same. Hash function from Mark Allen Weiss. 
 Any other resources used will be linked to within the document.*/

/*NOTE: i built my code on vscode, but i compiled it using cygwin on my linux machine. Vim was not producing proper results!*/

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include "hash.h"

//Initializing length of hash table for storing dictionary words.
#define MAXLENGTH 20

using namespace std;
hashTable dictionary(202481);

//Loading words from dictionary into hash table, comparing words in the document, and measuring and displaying length of task
//link: https://cplusplus.com/forum/beginner/241098/
void dictionaryLoad(ifstream &dictVal);
void spellcheck(ifstream &docVal, ofstream &outSpell);
void timeCheck(clock_t &startClk, clock_t &endClk, const string &time);

//User input: dictFile stores filename for dictionary, docFile inputs documents, writeFile outputs.
int main(){
    string dictionaryFile, docFile, writeFile;

    //timeStart and timeEnd records start time and end time of tasks
    clock_t startClk, endClk;
    cout << "Enter the name of dictionary: ";
    cin >> dictionaryFile;
    ifstream dictVal(dictionaryFile.c_str());
    if(!dictVal){
        cerr << "ERROR: Could not open " << dictionaryFile << endl;
        exit(1);
    }

    startClk = clock();
    dictionaryLoad(dictVal);
    endClk = clock();
    //function used to print time.
    timeCheck(startClk, endClk, "load dictionary");
    dictVal.close();

//User input field.
    cout << "Enter the name of input file: ";
    cin >> docFile;
    //link: https://stackoverflow.com/questions/6790821/cannot-read-input-file-ifstream*/
    ifstream docVal(docFile.c_str());
    if(!docVal){
        cerr << "ERROR: Could not open " << docFile << endl;
        exit(1);
    }

  //input field for output files
    cout << "Enter the name of output file: ";
    cin >> writeFile;
    ofstream outSpell(writeFile.c_str());
    if(!outSpell){
        cerr << "ERROR: Could not open " << writeFile << endl;
        exit(1);
    }

//the spellcheck process is timed similarly to dictionary loading
    startClk = clock();
    spellcheck(docVal, outSpell);
    endClk = clock();
    timeCheck(startClk, endClk, "check document");

    return 0;
}

//Function to read the dictionary line by line.
void dictionaryLoad(ifstream &dictVal){
    string line;
     /*In order to make sure the case doesn't impact spellcheck, everything is converted to lowercase through tansform().
    Then, the word is inserted into the hash table. 
    Link: https://stackoverflow.com/questions/5539249/why-cant-transforms-begin-s-end-s-begin-tolower-be-complied-successfu*/
    while(getline(dictVal, line)){
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        dictionary.insert(line);
    }
}

//Spellcheck for the document: checks valid characters, numbers, current # of lines in doc, and indices used to extract words from line. 
void spellcheck(ifstream &docVal, ofstream &outSpell){
 string validcharacters = "abcdefghijklmnopqrstuvwxyz0123456789'-",
        numbers = "0123456789", line, word; 
    int lineNum = 1, wordStart, wordEnd;

    //the document is read line by line and converted to lowercase. link: https://stackoverflow.com/questions/5343173/returning-to-beginning-of-file-after-getline
    while(getline(docVal, line)){
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        if(line==""){
            lineNum++;
            continue;
        }
    //words are then extracted by finding valid characters. find_first_of() locates the start of the word, and find_first_not_of() locates end.

        wordStart = line.find_first_of(validcharacters, 0);
        while(wordStart < line.length()){ 
            wordEnd = line.find_first_not_of(validcharacters, wordStart);
            if(wordEnd == -1){
            wordEnd = line.length(); 
            }
            word = line.substr(wordStart, wordEnd - wordStart);

    //if a word contains numbers, it is skipped.
    //link: https://cplusplus.com/reference/string/string/find_first_of/
    if(word.find_first_of(numbers) != -1){
    wordStart = line.find_first_of(validcharacters, wordEnd+1);
    continue; 
    }
    //if the word exceeds maximum length, that is reported in the ouput file. 
            else if(word.length() > MAXLENGTH){
                outSpell << "Long word at line " << lineNum << ", starts: " << word.substr(0, MAXLENGTH) << endl;
            }
    //if the word isn't found in the dictionary, then the program returns false, and it is considered unknown.
    else if(!dictionary.contains(word)){
        outSpell << "Unknown word at line " << lineNum << ": " << word << endl;}
            wordStart = line.find_first_of(validcharacters, wordEnd+1);}
        lineNum++;}   
}

//function calculates the time difference between start and end times, and prints results. 
void timeCheck(clock_t &startClk, clock_t &endClk, const string &time){
    float difference = (double(endClk - startClk))/CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to " << time << ": " << difference << endl;
}
