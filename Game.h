#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "ItemCatalog.h"
#include "Bestiary.h"
#include "Store.h"
#include "Map.h"
#include "Helper.h"

class Game
{
    protected:
        // Identifiers for the stores in the "stores" array. Each store corresponds to a specific type of item, and a specific stat to be altered.
        static const int healthStore = 0;
        static const int staminaStore = 1;
        static const int attackStore = 2;
        static const int defenseStore = 3;
        
        Player myPlayer;

        Store stores[4];
        ItemCatalog myItemCatalog;
        Bestiary myBestiary;
        Map dreams[9];
        Helper myHelper;

    public:
        Game(); // establishes environment

        void gameTest();
        void gameRun();
        void gameStart();

        void endGame();
        void endPrintShade();
        void endPrintLight();

        int genLoadBestiary(string filename);
        int genLoadItems(string filename); 
        void genGameSetup();
        void genPrintSpecialItem();
        void genPrintTutorial();
        void genPrintFinalReport(); 
        void genSaveFinalReport(); 
        void genLoadStores(int storeId, string itemCodes[], int codesSize);
        void genDisplayInventory();
        /* void genLoadSaveData(): would load data from save file. 
        save functionality (saving the game and restoring that save) for the future.
        */
        
        void equipItem();
        void equipGemstone(int itemIndex, int inventorySlot);
        void equipJewelry(int itemIndex, int inventorySlot);
        void equipWeapon(int itemIndex, int inventorySlot);
        void useItem(int itemIndex, int inventorySlot);

        void menuMain(); 
        void menuArena();
        void menuDream();
        void menuMarket();

        int shopPurchaseItem(int storeID, int storeSlot);
        int shopSellItem(int inventorySlot);
        void shopDisplayMenu(int storeID);
        void shopDisplayWares(int storeID);
        void shopMakeSale();

        int itemGetModAt(int slot);
        void itemDisplayDetails(int itemIndex);
        void itemGetDetails();
        string itemGetNameAt(int slot);

        int battleMain();
        bool battleMinion();
        bool battleShade();

        void dreamCorruptMagic();
        void dreamFindLoot();
        int dreamPrintShade();
        int dreamPrintMinion();
        void dreamRandomizeSpawn();

};
#endif