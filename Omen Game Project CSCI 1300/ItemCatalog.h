#ifndef ITEMCATALOG_H
#define ITEMCATALOG_H

#include "Player.h"
#include "Helper.h"

class ItemCatalog
{
    protected:
        static const int maxItems = 40;
        int numItems = 0;

        // The below arrays correspond to the data for each item. Item data is stored as lines in "items.txt". The arrays are synced over the same index.
        string code[maxItems]; 
        string name[maxItems];
        int modifier[maxItems];
        char type[maxItems];
        string desc[maxItems];
        int uses[maxItems];

        // Booleans that are used for tracking special items. If the player has found one of them, then its boolean will be set to true. Prevents duplicate special items.
        bool vialFound;
        bool weaponFound;
        bool gemstoneFound;
        bool jewelryFound;

    public:
        ItemCatalog();

        bool getVialFound();
        bool getWeaponFound();
        bool getGemstoneFound();
        bool getJewelryFound();

        void setVialFound(bool truth);
        void setWeaponFound(bool truth);
        void setGemstoneFound(bool truth);
        void setJewelryFound(bool truth);

        int getMaxItems();
        int getIndex(string code);

        int getModifier(int index);
        char getType(int index);
        string getCode(int index);
        string getName(int index);
        string getDesc(int index);
        int getUses(int index);
        void updateUses(int newUses, int index);
        void setUses(int newUses, int index);

        void setModifier(int newMod, int index);
        void setType(char newType, int index);
        void setCode(string newCode, int index);
        void setName(string newName, int index);
        void setDesc(string newDesc, int index);

        int findSalePrice(int index);
        int findPrice(int index);


};
#endif