#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
using namespace std;

#include "ItemCatalog.h"

class Player {
    
    private:
        /*
        The static values are the maximum amount of items a player can have in their equipment or inventory, and the maximum level they can reach before the game will end.
        Their inventory and equipment arrays are arrays of item indexes, which correlate to the Item Catalog.

        Corruption is a mechanic that works similarly to "Frustration", though its exact value is kept invisible. It determines what ending the player will get.
        As well, reaching a corruption level that is too high will alter the player's stats (boosting their health by 1).
        It is based on the player's successes and/or losses in battle against the monsters. 

        The tutorial boolean determines if the player will be shown guides about how some functions of the game work (ex. how to read the map).
        */
        static const int maxInventory = 9;
        static const int maxEquipment = 3;
        static const int maxLevel = 9;

        bool tutorial;

        string name;
        char magic;
        int corruption;
        int level;
        
        int health;
        int maxHealth;
        int stamina;
        int attack;
        int defense; 

        int wallet;
        int inventory[maxInventory];
        int equipment[maxEquipment];

    public:
        Player();

        bool getTutorial();
        void setTutorial(bool setting);

        string getName();
        void setName(string input);

        char getMagic();
        void setMagic(char input);
        void setMagicStats(char input);
        void resetAttack();
        void resetStamina();
        void resetDefense();
        void resetHealth();
        void displayMagic();

        int getLevel();
        void setLevel(int lvl);
        void updateLevel (int lvl);
        void displayLevel();
        int getMaxLevel();
        void levelUp(int lvl);

        void displayBasicStats();
        void displayStats();

        int getHealth();
        int getMaxHealth();
        void setHealth(int newHealth);
        void setMaxHealth(int health);
        void updateHealth(int healthPoints);
        void updateMaxHealth(int healthPoints);
        void displayHealth();

        int getStamina();
        void setStamina(int newStamina);
        void updateStamina(int staminaPoints);
        void displayStamina();

        int getAttack();
        void setAttack(int newAttack);
        void updateAttack(int attackPoints);
        void displayAttack();

        int getDefense();
        void setDefense(int newDefense);
        void updateDefense(int defensePoints);
        void displayDefense();

        int getWallet();
        void setWallet(int totalMoney);
        void updateWallet(int newMoney);
        void displayWallet();

        int getInventoryAt(int slot);
        void addInventory(int itemIndex);
        void removeInventoryAt(int slot);
        int getMaxInventory();
        int getMaxEquipment();

        void addEquipmentAt(int slot, int itemIndex);
        void removeEquipmentAt(int slot);
        int getEquipmentAt(int slot);

        int getGemstone();
        int getJewelry();
        int getWeapon();
        void setWeapon(int itemIndex);
        void setGemstone(int itemIndex);
        void setJewelry(int itemIndex);

        int getCorruption();
        void setCorruption(int corrupt);
        void updateCorruption(int corrupt);
};
#endif