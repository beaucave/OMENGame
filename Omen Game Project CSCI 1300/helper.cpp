#include "Helper.h"

char Helper::toLower(char subject)
{
    /*
    This function takes in a character, and changes the character to lowercase (if it is uppercase). It returns that lowercase-ified character.
    */
    if (subject >= 'A' && subject <= 'Z')
    {
        subject += 32;
    }
    return subject;

}

int Helper::split(string mainString, char separator, string pieceArray[], int arraySize)
{
    /*
    This function takes in a string of text, a seperator character, and an array to put the information into. It also passes the maximum size of the array.
    It moves through the string, saving each encountered character to a new string. When it encounters the seperator character, it saves that string to the information array.
    It then continues moving through, seperating the text between the previously-mentioned seperator and the next seperator into its own string for the array.
    It returns the total amount of items within the array. If the amount of items in the array ever exceeds the maximum array size, it returns -1 (indicating an error).
    */
    int length = mainString.length();
    int arrayStrings = 0;
    
    if (length == 0)
    {
        arrayStrings = 0;
        return arrayStrings;
    }


    for (int i = 0; i < length; i++)
    {
        char currentChar = mainString.at(i);
        if (currentChar == separator)
        {
            pieceArray[0+arrayStrings] = mainString.substr(0,i);
            i++; 
 
            mainString = mainString.substr(i, length-i);
            length -= i; 
            i = 0; 

            arrayStrings++;
        }
    }
    
    pieceArray[0+arrayStrings] = mainString; 
    arrayStrings++;

    if (arrayStrings > arraySize) 
    {
        arrayStrings = -1;
    }

    return arrayStrings;
}
