#ifndef STORE_H
#define STORE_H

#include "Player.h"
#include "ItemCatalog.h"

class Store // used during startup
{
    private:
        static const int maxWares = 9;
        int wares[maxWares];

    public:
        Store();

        int getItemAt(int slot); // returns the code of the item at the store index
        void setItemAt(int slot, int itemIndex);
        void removeItemAt(int slot);
        int getMaxWares();
        
};
#endif