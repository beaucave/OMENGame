#include "Bestiary.h"

Bestiary::Bestiary()
{
    for (int i = 0; i < maxMonsters; i++)
    {
        code[i] = "";
        title[i] = "";
        type[i] = 'x'; // x = null character
        level[i] = -1;
        rank[i] = 'x';
    }
}


/* Getters
The int/string getters return specific data about a given item; its name, description, code, etc.
getMaxMonsters() returns the maximum possible number of items that the Bestiary can store.
*/
char Bestiary::getRank(int index)
{
    return rank[index];
}
char Bestiary::getType(int index)
{
    return type[index];
}
int Bestiary::getIndex(string soughtCode)
{
    int index = -1;
    for (index = 0; index < maxMonsters; index++)
    {
        string current = code[index];
        if(current == soughtCode)
        {
            return index;
        }
    }
    return index;
}
int Bestiary::getLevel(int index)
{
    return level[index];
}
int Bestiary::getMaxMonsters()
{
    return maxMonsters;
}
string Bestiary::getCode(int index)
{
    string codee = code[index];
    return codee;
}
string Bestiary::getDesc(int index)
{
    return desc[index];
}
string Bestiary::getTitle(int index)
{
    return title[index];
}

/* Setters
These set the values of various monster attributes. They're used to initialize the main monster arrays (enabling the use of item indexes for inventory/equipment/store functions).
*/
void Bestiary::setCode(int index, string newCode)
{
    code[index] = newCode;
}
void Bestiary::setLevel(int index, int newLevel)
{
    level[index] = newLevel;
}
void Bestiary::setRank(int index, char newRank)
{
    rank[index] = newRank;
}
void Bestiary::setType(int index, char newType)
{
    type[index] = newType;
}
void Bestiary::setTitle(int index, string newTitle)
{
    title[index] = newTitle;
}
void Bestiary::setDesc(int index, string newDesc)
{
    desc[index] = newDesc;
}
