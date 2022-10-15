#include "Player.h"

Player::Player()
{
    /*
    This creates an empty Player object with some default stats assigned; their level, their health, and how much money they have.
    This empty player is later updated with specific information about their name and magic.
    */
    name = "";
    level = 1;
    magic = 'X';
    corruption = 0;

    maxHealth = 3;
    health = maxHealth;
    stamina = 0;
    attack = 0;
    defense = 0;

    wallet = 10;

    for (int i = 0; i < maxInventory; i++)
    {
        inventory[i] = -1; // representing an empty item
    }

    for (int i = 0; i < maxEquipment; i++)
    {
        equipment[i] = -1;
    }
}

/* Initial Functions
These functions are used to determine if the player enabled the tutorial, and what they want their name to be.
They update the plyer object (and return information from it) as needed.
*/
bool Player::getTutorial()
{
    return tutorial;
}
void Player::setTutorial(bool setting)
{
    tutorial = setting;
}

string Player::getName()
{
    return name;

}
void Player::setName(string input)
{
    name = input;
}

/* Magic Functions
These functions deal with what kind of magic the player has; accessing what kind of magic the player has, initially setting that value, and altering their stats based on that value. 
See "setMagicStats" for more details.
*/
char Player::getMagic()
{
    return magic;
}
void Player::setMagic(char input)
{
    magic = input;
}
void Player::setMagicStats(char input)
{
    /*
    The player's stats will change based on what magic they select. 
    Blue magic will boost their stamina, Red will boost their attack, and Green will boost their defense.
    Black magic is selectable from the start, though it isn't visible as an option. That boosts all the player's stats immediately, including their health.
    */
    switch (input)
    {
        default: // nonmagical player
        {
            health = 3;
            stamina = 1;
            attack = 1;
            defense = 0;
            setMaxHealth(health);
            break;            
        }
        case 'B': // blue
        {
            health = 3;
            stamina = 1 + level;
            attack = 1;
            defense = 0;
            setMaxHealth(health);
            break;
        }
        case 'R': // red
        {
            health = 3;
            stamina = 1;
            attack = 1 + level;
            defense = 0;
            setMaxHealth(health);
            break;
        }
        case 'G': // green
        {
            health = 3;
            stamina = 1;
            attack = 1;
            defense = 0 + level;
            setMaxHealth(health);
            break;
        }
        case 'K': // black
        {
            health = 3 + level;
            stamina = 1 + level;
            attack = 1 + level;
            defense = 0 + level;
            setMaxHealth(health);
            break;
        }
    }

}

/* Reset Functions
These functions will reset a player's stat based on their level and magic type; they're used in the process of equipping/de-equipping items.
Each statistic is influenced by the player's magic. 
For example, if the player has Red magic, their reset Attack value will be calculated using both their level and an additional +1 modifier from that magic.
Black magic will always give these reset functions an additional +1 boost.

The calculations are all sums. For example, if the player was level 3, their attack stat would be determined like this:
    1 (the default value) + 3 (their level).
If that player had Red or Black magic, then their attack stat would be determined like this:
    1 (the default value) + 3 (their level) + 1 (a modifier from their magic).
*/
void Player::resetAttack()
{
    if (magic == 'R' || magic == 'K')
    {
        attack = 1 + level + 1;
    }
    else
    {
        attack = 1 + level;
    }
}
void Player::resetStamina()
{
    if (magic == 'B' || magic == 'K')
    {
        stamina = 1 + level + 1;
    }
    else
    {
        stamina = 1 + level;
    }
}
void Player::resetDefense()
{
    if (magic == 'G' || magic == 'K')
    {
        defense = level;
    }
    else
    {
        defense = level - 1;
    }
}
void Player::resetHealth()
{
    if (magic == 'K')
    {
        health = 3 + level + 1;
    }
    else
    {
        health = 3 + level;
    }
}

/* Level & Statistic Functions
Level and & Statistic functions follow the same general structure.

Getters: return the value of the relevant stat.
Setters: takes in a value, and sets the relevant stat to that value.
Updates: takes a value, and updates the value of the relevant stat by whatever amount is input. The update is done via addition; the change value can be positive or negative.
Displays: outputs the current value of the relevant statistic.

The maxHealth functions determine the maximum health a player may have based on their level.

Special Functions (with more detailed explanations): displayBasicStats, displayStats, levelUp.
*/
void Player::displayBasicStats()
{
    /*
    This function outputs the player's current level and remaining health. 
    */
    cout << getName() << ":" << endl;
    cout << "You're currently Level " << getLevel()  << "." << endl;
    cout << "You have " << getHealth() << " health remaining." << endl;
}
void Player::displayStats()
{
    /*
    This functions outputs the values of all of the player's stats; the basic stats (see above) as well as their attack, defense, and stamina.
    */ 
    cout << "Here are all of your stats." << endl;
    displayLevel();
    displayHealth();
    displayStamina();
    displayAttack();
    displayDefense();
    cout << endl;
}
int Player::getMaxHealth()
{
    return maxHealth;
}
void Player::setMaxHealth(int health)
{
    maxHealth = health;
}
void Player::updateMaxHealth(int healthPoints) 
{
    maxHealth += healthPoints; // can be positive or negative
}

int Player::getLevel()
{
    return level;
}
int Player::getMaxLevel()
{
    return maxLevel;
}
void Player::setLevel(int lvl)
{
    level = lvl;
}
void Player::updateLevel (int lvl)
{
    level += lvl;
}
void Player::displayLevel()
{
    cout << "Level: " << getLevel() << endl;
}
void Player::levelUp(int lvl)
{
    /*
    This function takes in an amount to change the player's level by. It ISN'T the new level; it's the difference between the new and old one.
    It updates each stat with that change value, and resets the player's health to fully heal them.
    */
    updateLevel(lvl);
    updateAttack(lvl);
    updateDefense(lvl);
    updateStamina(lvl);
    updateMaxHealth(lvl);
    setHealth(getMaxHealth());
}

int Player::getHealth()
{
    return health;
}
void Player::setHealth(int newHealth)
{
    health = newHealth;
}
void Player::updateHealth(int healthPoints) 
{
    health += healthPoints; // can be positive or negative
}
void Player::displayHealth()
{
    cout << "HP: " << health << "/" << maxHealth << endl;
}

int Player::getStamina()
{
    return stamina;
}
void Player::setStamina(int newStamina)
{
    stamina = newStamina;
}   
void Player::updateStamina(int staminaPoints)
{
    stamina += staminaPoints;
}
void Player::displayStamina()
{
    cout << "STAMINA: " << stamina << endl;
}

int Player::getAttack()
{
    return attack;
}
void Player::setAttack(int newAttack)
{
    attack = newAttack;
}
void Player::updateAttack(int attackPoints)
{
    attack += attackPoints;
}
void Player::displayAttack()
{
    cout << "ATK: " << attack << endl;
}

int Player::getDefense()
{
    return defense;
}
void Player::setDefense(int newDefense)
{
    defense = newDefense;
}
void Player::updateDefense(int defensePoints)
{
    defense += defensePoints;
}
void Player::displayDefense()
{
    cout << "DEF: " << defense << endl;
}

/* Inventory Functions
The inventory functions deal with the player's items and how they move things in and out of them.
*/
int Player::getMaxInventory()
{
    return maxInventory;
}
int Player::getInventoryAt(int slot)
{
    return inventory[slot];
}
void Player::addInventory(int itemIndex)
{
    /*
        This function will add an item to the most recent empty slot in the player's inventory.
        If all slots are filled, it will print "Your inventory is full! To make room, try selling items or consuming a potion!"
        It will then return the player to their inventory as printed in displayInventory().
    */
   for (int i = 0; i < maxInventory; i++)
    {
        int current = inventory[i];
        if (current == -1)
        {
            inventory[i] = itemIndex;
            return;
        }
    }

    cout << "Your inventory is full. Sell or use up an item to free up space!" << endl;

}
void Player::removeInventoryAt(int inventorySlot)
{
    /*
        This function is used to remove an item from the inventory. For single-use items or selling items.
    */
   inventory[inventorySlot] = -1;
}

/* Wallet Functions
These functions are very similar to the level/stat functions above. The descriptions for general function types -- "getters, setters, updates" etc -- are the same here.
*/
int Player::getWallet()
{
    return wallet;
}
void Player::setWallet(int totalMoney)
{
    wallet = totalMoney;
}
void Player::updateWallet(int newMoney)
{
    wallet += newMoney;
}
void Player::displayWallet()
{
    cout << "You have " << wallet << " dollars." << endl;
    char cont;
    cout << "Press any key to continue" << endl;
    cin >> cont;
}

/* Equipment Functions
The equipment functions are just getters and setters. The getters take the index of the item currently equipped (or -1, indicating an empty slot).
The setters will update the equipment slots with new items. The actual equipping process takes place in the Game class.
*/
int Player::getWeapon()
{
    return equipment[0];
}
void Player::setWeapon(int itemIndex)
{
    equipment[0] = itemIndex;
}
int Player::getGemstone()
{
    return equipment[1];
}
void Player::setGemstone(int itemIndex)
{
    equipment[1] = itemIndex;
}
int Player::getJewelry()
{
    return equipment[2];
}
void Player::setJewelry(int itemIndex)
{
    equipment[2] = itemIndex;
}

/* Corruption Functions
The corruption functions operate similarly to the statistic functions. The getter returns the player's current corruption value. The setter will take in a new value, and overwrite the old one. 
The update function will take in a new value, and add it to the current corruption total; either positive or negative. A player's corruption CAN be a negative number.
*/
int Player::getCorruption()
{
    return corruption;
}
void Player::setCorruption(int corrupt)
{
    corruption = corrupt;
}
void Player::updateCorruption(int corrupt)
{
    corruption += corrupt; 
}