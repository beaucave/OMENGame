#ifndef BESTIARY_H
#define BESTIARY_H

#include <iostream>
#include <fstream>
using namespace std;

#include "Player.h"

class Bestiary // see: "ItemCatalog.h"
{
    protected:
        static const int maxMonsters = 30; // will be updated as more monsters are completed
        
        string code[maxMonsters];
        string title[maxMonsters];
        string desc[maxMonsters];
        int level[maxMonsters]; // modifies its type stat by this
        char type[maxMonsters]; // R/G/B/K; magiv type
        char rank[maxMonsters]; // Shade (boss) or minion
    
    public:
        // constructors
        Bestiary();

        int getMaxMonsters();
        int getIndex(string code); // the actual item used in store/inventory
        string getCode(int index);
        int getLevel(int index); // modifies both player stat and store price; division errors -> double?
        char getRank(int index);
        char getType(int index);
        string getTitle(int index);
        string getDesc(int index);
        
        void setCode(int index, string newCode);
        void setLevel(int index, int newLevel); // modifies both player stat and store price; division errors -> double?
        void setRank(int index, char newRank);
        void setType(int index, char newType);
        void setTitle(int index, string newTitle);
        void setDesc(int index, string newDesc);
};
#endif