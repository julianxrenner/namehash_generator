/*
Name: Julian Renner
Date: March 21, 2023
Decription: write a program named assignment 9 in C++ that creates a hash table for names (first and last only), when done loading, the contents are then printed out
*/
#include <iomanip>	//allows the program to use formatting options like setw
#include <iostream>	//allows the program to use input and output
#include <fstream>	//allows the progrom to use files
#include <cmath>    //allows use of math operations
#include <string>	// allows use of strtok

using namespace std;	//allows the program to use cout and cin

const int MAXSIZE = 256; // integer constant max for hash table


struct htEntry { // structure for entry
    bool occupied = false; // boolean for entry occupied and set to false
    string name = ""; // string to store name related to the entry
    struct htEntry* nextPtr = NULL; // pointer to htEntry structure for next entry in hash table initialized to null
};

unsigned char generateKey(string); // prototype function creates key for string

int main() {
    struct htEntry hashTable[MAXSIZE]; // structure array named htEntry of MAXSIZE(256)

    string inFilen; // string that stores name of input file
    string name; // string to store the name from file

    cout << "Enter the name of file you wish to open: ";
    cin >> inFilen;

    ifstream inputFile(inFilen);

    if (inputFile.fail()) {
        cout << "Cannot open " << inFilen <<endl;
        return 1;
    }

    while (getline(inputFile, name)) {
        unsigned char key = generateKey(name); // unsigned char to store created key for name
        if (hashTable[key].occupied == false) { // If key's entry is unoccupied add name to entry
            hashTable[key].occupied = true;
            hashTable[key].name = name;
        }

        else { // If key's entry is occupied, add name to chain of entries for key
            struct htEntry* newPtr = new struct htEntry; // pointer to htEntry structure to create new entry for name
            newPtr->occupied = true;
            newPtr->name = name;
            newPtr->nextPtr = NULL;
            struct htEntry* currentPtr = &hashTable[key]; // pointer to htEntry structure to find last entry in chain for key

            while (currentPtr->nextPtr != NULL) {
                currentPtr = currentPtr->nextPtr;
            }
            currentPtr->nextPtr = newPtr;
        }
    }
    inputFile.close();

    for (int a = 0; a < MAXSIZE; a++) {
        if (hashTable[a].occupied) { // If entry occupied, print name related to it
            cout << "Slot " << a << " is occupied with " << hashTable[a].name;
            struct htEntry* currentPtr = hashTable[a].nextPtr; // pointer to htEntry, and currentPtr is nextPtr of ith entry
            while (currentPtr != NULL) {
                cout << "\t" << currentPtr->name;
                currentPtr = currentPtr->nextPtr;
            }
            cout << endl;
        }
    }

    return 0;
}

//function generates a key for a given string. Function  takes a string
//for the name associated with the entry of the hash table
unsigned char generateKey(string name) {
    unsigned char key = 0; // unsigned char key equal to zero
    for (int a = 0; a < name.length(); a++) {
        key ^= name[a]; // XOR all chars in the name
    }

    return key;
}