#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <fstream>
using namespace std;

class Helper 
{
    public:
    /*
    The helper class contains functions that can aid other functions. 
    For example, split is used by "loadItems" and "loadBestiary" to collect the information from the text files correctly.
    */
    char toLower(char subject);
    int split(string mainString, char separator, string pieceArray[], int arraySize);
};

#endif
