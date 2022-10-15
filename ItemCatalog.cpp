#include "ItemCatalog.h"

ItemCatalog::ItemCatalog()
{
    /*
    Constructs an empty array that can then be filled with items.
    */
    for (int i = 0; i < maxItems; i++)
    {
        code[i] = "";
        name[i] = "";
        type[i] = 'x'; // x = null character
        modifier[i] = -1;
        desc[i] = "";
        uses[i] = -1;
    }
    numItems = 0;
}

void ItemCatalog::updateUses(int newUses, int index)
{
    /*
    Takes in the index of an item and the amount to add to its uses (positive or negative).
    This updates the uses for a given item, to indicate if its been consumed.
    */
    uses[index] += newUses;
}

int ItemCatalog::findPrice(int index)
{
    /*
    Takes in the index of an item and calculates the price it can be bought for. It's greater than the amount the same item could be sold for. 
    Returns that calculated price.
    */

    int basePrice = 12;
    int modPrice = getModifier(index);

    int itemPrice = basePrice * modPrice;
    return itemPrice;
}
int ItemCatalog::findSalePrice(int index)
{
    /*
    Takes in the index of an item and calculates the money it can be sold for. It is lower than the purchase price by about 17% percent (10 versus 12). 
    Returns that calculated value.
    */
    int basePrice = 10;
    int modPrice = getModifier(index);

    int itemPrice = basePrice * modPrice;
    return itemPrice;
}

/* Getters
The int/string getters return specific data about a given item; its name, description, code, etc.
The boolean getters return whether or not a player has previously encountered the relevant special item.
getMaxItems() returns the maximum possible number of items that the Item Catalog can store.
*/
int ItemCatalog::getMaxItems()
{
    return maxItems;
}
bool ItemCatalog::getVialFound()
{
    return vialFound;
}
bool ItemCatalog::getWeaponFound()
{
    return weaponFound;
}
bool ItemCatalog::getGemstoneFound()
{
    return gemstoneFound;
}
bool ItemCatalog::getJewelryFound()
{
    return jewelryFound;
}
char ItemCatalog::getType(int index)
{
    char magicType = type[index];
    return magicType;
}
int ItemCatalog::getIndex(string soughtCode)
{
    int index = -1;
    for (index = 0; index < maxItems; index++)
    {
        string current = code[index];
        if(current == soughtCode)
        {
            return index;
        }
    }
    return index;
}
int ItemCatalog::getModifier(int index)
{
    int mod = modifier[index];
    return mod;
}
int ItemCatalog::getUses(int index)
{
    return uses[index];
}
string ItemCatalog::getCode(int index)
{
    string codee = code[index];
    return codee;
}
string ItemCatalog::getDesc(int index)
{
    string descriptor = desc[index];
    return descriptor;
}
string ItemCatalog::getName(int index)
{
    string title = name[index];
    return title;
}

/* Setters
These set the values of various item attributes. They're used to initialize the main item arrays (enabling the use of item indexes for inventory/equipment/store functions).
They're also used to track if special items have been countered.
*/
void ItemCatalog::setVialFound(bool truth)
{
    vialFound = truth;
}
void ItemCatalog::setWeaponFound(bool truth)
{
    weaponFound = truth;
}
void ItemCatalog::setGemstoneFound(bool truth)
{
    gemstoneFound = truth;
}
void ItemCatalog::setJewelryFound(bool truth)
{
    jewelryFound = truth;
}
void ItemCatalog::setCode(string newCode, int index)
{
    code[index] = newCode;
}
void ItemCatalog::setDesc(string newDesc, int index)
{
    desc[index] = newDesc;
}
void ItemCatalog::setModifier(int newMod, int index)
{
    modifier[index] = newMod;
}
void ItemCatalog::setName(string newName, int index)
{
    name[index] = newName;
}
void ItemCatalog::setType(char newType, int index)
{
    type[index] = newType;
}
void ItemCatalog::setUses(int newUses, int index)
{
    uses[index] = newUses;
}
