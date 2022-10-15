#include "Store.h"

Store::Store()
{
    for (int i = 0; i < maxWares; i++)
    {
        wares[i] = -1;
    }
}

int Store::getItemAt(int slot) // returns the code of the item at the store index
{
    return wares[slot-1];
}

void Store::setItemAt(int slot, int itemIndex)
{
    wares[slot-1] = itemIndex;
}

int Store::getMaxWares()
{
    return maxWares;
}

void Store::removeItemAt(int slot)
{
    setItemAt(slot, -1);
}