#include "Game.h"
#include "Helper.h"

Game::Game()
{
    myPlayer = Player();

    myItemCatalog = ItemCatalog();
    myBestiary = Bestiary();

    myHelper = Helper();
}

/* Game Functions
    Game functions are used to actually execute the game and call all relevant functions. Some run the tutorial, some take care of ending the game, and "gameRun"... runs the game.
    ... You may have guessed that last part.
*/
void Game::gameRun()
{
    genGameSetup();
    gameStart();
    menuMain();
    endGame();
}
void Game::gameStart()
{
    /*
    The player can input their name, and decide whether or not to run the tutorial. They also can pick their magic type (which impacts their stats).
    It also provides the player with their starter equipment (a baseball bat).
    */
    string playerName;

    cout << "Hi! What's your name?" << endl;
    getline(cin, playerName);
    myPlayer.setName(playerName);

    char introduction;
    cout << "Welcome to ILDA, " << playerName << "! This world is one very similar to our own... but with a little bit of magic to it. ";
    cout << "Would you like a formal introduction, or do you know your way around already? (Y or N)." << endl;
    cout << "Y. Introduce me!" << endl;
    cout << "N. I know what I'm doing!" << endl;
    cin >> introduction;

    if (introduction == 'Y')
    {
        myPlayer.setTutorial(true);
        genPrintTutorial();
    }
    else
    {
        myPlayer.setTutorial(false);
        char magicType;
        cout << endl
             << "Pick your magic: Red (improves ATK), Green (improves DEF), or Blue (improves STAMINA)." << endl;
        cout << "R. Red" << endl;
        cout << "G. Green" << endl;
        cout << "B. Blue" << endl;

        while (magicType != 'R' || magicType != 'G' || magicType != 'B' || magicType != 'K')
        {
            cin >> magicType;
            if (magicType != 'R' && magicType != 'G' && magicType != 'B' && magicType != 'K')
            {
                cout << "That's not magic! Enter R, G, or B." << endl;
                continue;
            }
            else if (magicType == 'K')
            {
                cout << "Either you're an experienced fighter, or you've stumbled into something you don't understand. Either way... " << endl;
                cout << "The light seems to dim around your fingers." << endl
                     << endl;
                break;
            }
            else
            {
                break;
            }
        }

        myPlayer.setMagic(magicType);
        myPlayer.setMagicStats(magicType);
        myPlayer.addInventory(myItemCatalog.getIndex("weapon0"));

        myPlayer.setWeapon(myItemCatalog.getIndex("weapon0"));
        cout << "You enter ILDA, armed with an old baseball bat and your wits." << endl;
    }
}
void Game::gameTest()
{
    /*
        This function is used to test specific menus or functions. Used for developmental/testing purposes.
    */
    genGameSetup();

    myPlayer.setMagicStats('B');
    myPlayer.levelUp(2);

    int bat = myItemCatalog.getIndex("weapon0");
    myPlayer.addInventory(bat);
    myPlayer.setWeapon(bat);

    myPlayer.updateWallet(24);
    myPlayer.setStamina(60);

    menuMain();
}
void Game::endGame()
{
    /*
    This function runs after players meet the "end conditions"; defeating the final monster and levelling up to 10.
    Future end conditions may be added later, such as reaching a certain corruption threshold. Currently, other end conditions do not exist.

    If the player has won enough battles, then they will have the "Light" ending; see: "endPrintLight".
    If they've lost too many battles, then they'll have the "Shade" ending, where they become one of the monsters they once hunted. See: "endPrintShade".

    After seeing their ending, players can choose to see their final data (stats, inventory items, etc.). The data is not processed, so some information is left as index numbers (inventory items, etc).
    */
    cout << endl;

    int corruption = myPlayer.getCorruption();

    if (corruption < 50)
    {
        endPrintLight();
    }
    if (corruption >= 50)
    {
        endPrintShade();
    }

    cout << endl
         << "You've done all you can do. It's time to go." << endl;
    cout << "Would you like to view your final player data? (Y or N)" << endl;
    char report;

    while (report != 'Y' && report != 'N')
    {
        cin >> report;

        if (report == 'Y')
        {
            genPrintFinalReport();
            cout << endl;
            return;
        }
        else if (report == 'N')
        {
            return;
        }
        else
        {
            cout << "That's not possible. Enter Y or N!" << endl;
            break;
        }
    }
}
void Game::endPrintLight()
{
    cout << "You've managed to destroy the ninth DREAM. You feel light, for the first time in a long time." << endl;
    cout << "This magic has always walked the line between a blessing and curse. Despite everything..." << endl;
    cout << "You have new hope." << endl;
}
void Game::endPrintShade()
{
    cout << "You've finished that final battle, but you've lost too much." << endl;
    cout << "Your magic has turned dark and bitter and hungry. Maybe your magic has always been this way, and you've only just been able to see it clearly." << endl;
    cout << "The world around you becomes light, and then an absence of it. Your magic is beyond your control, now." << endl;
    cout << endl;
    cout << "A new SHADE has hatched." << endl;
}

/* General Functions
    General (or Miscellaneous) functions are functions that do not directly impact player activity or only output text. Some of these are "background" processes.
    These background processes load information from text files into arrays, so the player can interact with that information.
*/
int Game::genLoadBestiary(string filename)
{
    /*
    Functions similarly to "genLoadItems". Loads items from the "monsters.txt" text file into multiple Bestiary member arrays. Each array is synced over the same index,
    meaning one monster's index can be used to access their title, description, level, etc.
    */

    ifstream myFile;
    myFile.open(filename);

    string currentLine;
    int numMonsters = 0;

    while (getline(myFile, currentLine))
    {
        if (currentLine == "")
        {
            continue;
        }
        string splitArray[6];
        myHelper.split(currentLine, '_', splitArray, 6);

        myBestiary.setCode(numMonsters, splitArray[0]);
        myBestiary.setTitle(numMonsters, splitArray[1]);
        myBestiary.setType(numMonsters, splitArray[2].at(0));
        myBestiary.setLevel(numMonsters, stoi(splitArray[3]));
        myBestiary.setRank(numMonsters, splitArray[4].at(0));
        myBestiary.setDesc(numMonsters, splitArray[5]);

        numMonsters++;
    }

    myFile.close();

    return numMonsters;
}
int Game::genLoadItems(string filename)
{
    /*
    Loads items from the inventory text file -- "items.txt" into multiple Item Catalog member arrays. Each array is synced over the same index,
    meaning one item's index can be used to access their title, description, modifier, etc.
    Item indexes can be found via scanning for each item's code when necessary. Item indexes are what are transferred between store menus, the player's inventory, and the player's equipment.
    Data for each of those items is accessed via that index and specific Item Catalog methods.
    */

    ifstream myFile;
    myFile.open(filename);

    string currentLine;
    string splitArray[6];
    int numItems = 0;

    while (getline(myFile, currentLine))
    {
        if (currentLine == "")
        {
            continue;
        }

        int lineNum = myHelper.split(currentLine, '_', splitArray, 6);

        myItemCatalog.setCode(splitArray[0], numItems);
        myItemCatalog.setType(splitArray[1].at(0), numItems);
        myItemCatalog.setName(splitArray[2], numItems);
        int newMod = stoi(splitArray[3]);
        myItemCatalog.setModifier(newMod, numItems);
        myItemCatalog.setDesc(splitArray[4], numItems);
        int newUses = stoi(splitArray[5]);
        myItemCatalog.setUses(newUses, numItems);

        numItems++;
    }

    myFile.close();

    return numItems;
}
void Game::genDisplayInventory()
{
    /*
    This displays the title of each item in the player's inventory.
    If an inventory slot is blank, it will print the slot number with no information.
    */
    cout << "Your Inventory:" << endl;

    for (int itemSlot = 0; itemSlot < myPlayer.getMaxInventory(); itemSlot++)
    {
        int itemIndex = myPlayer.getInventoryAt(itemSlot);
        int inventorySlot = itemSlot + 1;

        cout << inventorySlot << ". " << myItemCatalog.getName(itemIndex) << endl;
    }
    cout << endl;
}
void Game::genGameSetup()
{
    /*
    Loads items and monsters into their relevant arrays, and spawns the 9 battle maps (DREAMS). Also populates the menus for each menu within the store.
    The string arrays are arrays of item codes, which are used to find indexes and populate each store map.
    */
    genLoadItems("items.txt");
    genLoadBestiary("monsters.txt");

    dreamRandomizeSpawn();

    string attackStoreItems[] = {
        "weapon1",
        "weapon2",
        "weapon3",
        "weapon4",
        "weapon5",
        "weapon6",
    };
    string defenseStoreItems[] = {
        "jewelry1",
        "jewelry2",
        "jewelry3",
        "jewelry4",
        "jewelry5",
        "jewelry6",
    };
    string staminaStoreItems[] = {
        "gemstone1",
        "gemstone2",
        "gemstone3",
        "gemstone4",
        "gemstone5",
        "gemstone6",
    };
    string hpStoreItems[] = {
        "vial1",
        "vial2",
        "vial3",
        "vial4",
        "vial5",
        "vial6",
    };

    genLoadStores(attackStore, attackStoreItems, 6);
    genLoadStores(defenseStore, defenseStoreItems, 6);
    genLoadStores(staminaStore, staminaStoreItems, 6);
    genLoadStores(healthStore, hpStoreItems, 6);
}
void Game::genLoadStores(int storeId, string itemCodes[], int codesSize)
{
    /*
        After the item catalog has been loaded, this saves specific items to the relevant store menus. Later accessed when the player is in RAVEN MARKET (the store).
    */
    for (int i = 0; i < codesSize; i++)
    {
        int slot = i + 1;
        stores[storeId].setItemAt(slot, myItemCatalog.getIndex(itemCodes[i]));
    }
}
void Game::genPrintFinalReport()
{
    /*
    Prints the final data from the player's save file.
    */
    string currentLine;
    string fileName = "save" + myPlayer.getName() + ".txt";

    ifstream myFile;
    myFile.open(fileName);

    while (getline(myFile, currentLine))
    {
        cout << currentLine << endl;
    }
}
void Game::genPrintSpecialItem()
{
    /*
    Text that is printed after a player finds a Special item.
    */
    cout << "It's likely in vain, but you hope that whoever wrote this is still alive. You'd like to thank them for the gift." << endl;
    cout << endl;
}
void Game::genPrintTutorial()
{
    /*
        A "game manual" of sorts, this explains the stats and possible actions that a player can take in-game. Can be selected upon starting; will enable future tutorial popups in the DREAM menu.
    */
    cout << endl
         << "-------" << endl;
    cout << "Here in Ilda, you're one of the unlucky ones. You're a Harbinger: someone cursed with magic power." << endl;
    cout << "Now, it's your duty to protect the rest of the world from magical dangers." << endl
         << endl;

    cout << "You have four stats that matter here. " << endl;
    cout << "(1) Your HEALTH POINTS, or HP: how many hits you can take before you drop." << endl;
    cout << "(2) Your STAMINA: how far you can move before you need to take a break." << endl;
    cout << "(3) Your ATK: how much damage you can do in one blow." << endl;
    cout << "(4) Your DEF: how much damage you can block or dodge." << endl;

    cout << "You can improve these stats with practice, special items, or by LEVELING UP!" << endl
         << endl;

    cout << "There are three things you can do here in ILDA:" << endl;
    cout << "(1) Visit LEVIATHAN, a secretive arena. Here, you can spar with, talk to, and learn from other magic-users." << endl;
    cout << "(2) Shop at RAVEN MARKET, a mysterious shop with unusual products and more unusual customers." << endl;
    cout << "(3) Enter a DREAM. Dreams are home to monstrous SHADES and their minions. Fighting them is risky, but earns you experience and can come with big rewards!" << endl
         << endl;

    cout << "Press Y to start." << endl;
    char ready = 'x';

    while (ready != 'Y')
    {
        cin >> ready;

        if (ready != 'Y')
        {
            cout << "It's good to prepare, but the monsters won't wait forever! Are you ready now?" << endl;
        }
    }

    cout << "Oh, one more thing! You need to pick your kind of magic. There are three types: " << endl;
    cout << "Red (improves ATK), Green (improves DEF), or Blue (improves STAMINA)." << endl;
    cout << "R. Red" << endl;
    cout << "G. Green" << endl;
    cout << "B. Blue" << endl;

    char magicType;

    while (magicType != 'R' || magicType != 'G' || magicType != 'B' || magicType != 'K')
    {
        cin >> magicType;
        if (magicType != 'R' && magicType != 'G' && magicType != 'B' && magicType != 'K')
        {
            cout << "That's not magic! Enter R, G, or B." << endl;
            continue;
        }
        else if (magicType == 'K')
        {
            cout << "Either you're an experienced fighter, or you've stumbled into something you don't understand. Either way... ";
            cout << "The light seems to dim around your fingers." << endl;
            break;
        }
        else
        {
            break;
        }
    }

    myPlayer.setMagic(magicType);
    myPlayer.setMagicStats(magicType);
}
void Game::genSaveFinalReport()
{
    /*
    Saves the current player data (level, stats, inventory, equipment) to a text file, labelled with that player's name.
    Writes to a file.
    */

    ofstream myFile;
    string fileName = "save" + myPlayer.getName() + ".txt";
    myFile.open(fileName);

    myFile << myPlayer.getName() << endl;
    myFile << myPlayer.getLevel() << endl;

    myFile << "Statistics (Health, Stamina, Attack, Defense)" << endl;

    myFile << myPlayer.getHealth() << endl;
    myFile << myPlayer.getStamina() << endl;
    myFile << myPlayer.getAttack() << endl;
    myFile << myPlayer.getDefense() << endl;

    myFile << "Equipment (Index Numbers; -1 indicates an empty slot)" << endl;

    myFile << myPlayer.getWeapon() << endl;
    myFile << myPlayer.getGemstone() << endl;
    myFile << myPlayer.getJewelry() << endl;

    myFile << "Inventory (Index Numbers; -1 indicates an empty slot)" << endl;

    for (int j = 0; j < myPlayer.getMaxInventory(); j++)
    {
        myFile << myPlayer.getInventoryAt(j) << endl;
    }

    myFile.close();

    return;
}

/* Equipment Functions
Equipment functions move items from the player's inventory to their equipment, and update their stats accordingly.
The useItem function is categorized as an equipment function.
*/
void Game::equipItem()
{
    /*
    The player selects an item (technically an item's index) from their inventory. Using that index, the item is moved into the "equipment" array and removed from the visible inventory.
    Each item type has a specific equipment slot in the equipment array, and will update only that slot, based on the item's type.
    If the item is a potion, it'll exit this function; potions cannot be equipped, after all.
    Specific item types each have their own specific equipment function (see other functions in this list).
    */
    int inventorySlot = -1;

    while (inventorySlot != 0)
    {
        genDisplayInventory();
        cout << "What item do you want to equip? Pick a number." << endl;
        cout << "0. Exit this menu." << endl;
        cin >> inventorySlot;

        if (inventorySlot == 0)
        {
            break;
        }

        int itemIndex = myPlayer.getInventoryAt(inventorySlot - 1);
        char type = myItemCatalog.getType(itemIndex);

        if (type == 'W')
        {
            equipWeapon(itemIndex, inventorySlot);
            inventorySlot = 0;
            break;
        }
        else if (type == 'J')
        {
            equipJewelry(itemIndex, inventorySlot);
            inventorySlot = 0;
            break;
        }
        else if (type == 'G')
        {
            equipGemstone(itemIndex, inventorySlot);
            inventorySlot = 0;
            break;
        }
        else
        {
            cout << "You can't equip that. Try something else!" << endl;
            break;
        }
    }
}
void Game::equipGemstone(int itemIndex, int inventorySlot)
{
    /*
    Takes the index of a gemstone and the inventory slot that it occupies.
    Updates the GEMSTONE slot in the equipment array, and removes it from the inventory.
    Updates the player's STAMINA stat based on the newly-equipped gem's modifier.
    */
    myPlayer.resetStamina();
    myPlayer.setGemstone(itemIndex);
    cout << "You equip the gemstone. Your STAMINA increases by +" << myItemCatalog.getModifier(itemIndex) << "." << endl;

    myPlayer.updateStamina(myItemCatalog.getModifier(itemIndex));
    cout << "Your STAMINA is now " << myPlayer.getStamina() << "." << endl;

    myPlayer.removeInventoryAt(inventorySlot);
}
void Game::equipJewelry(int itemIndex, int inventorySlot)
{
    /*
    Takes a jewelry piece's index and the inventory slot it occupies.
    Updates the JEWELRY slot in the equipment array, and removes it from the inventory.
    Updates the player's DEFENSE stat based on the newly-equipped gem's modifier.
    */
    myPlayer.resetDefense();

    myPlayer.setJewelry(itemIndex);
    cout << "You put on the jewelry. Your DEFENSE increases by +" << myItemCatalog.getModifier(itemIndex) << "." << endl;

    myPlayer.updateDefense(myItemCatalog.getModifier(itemIndex));
    cout << "Your DEF is now " << myPlayer.getDefense() << "." << endl;

    myPlayer.removeInventoryAt(inventorySlot);
}
void Game::equipWeapon(int itemIndex, int inventorySlot)
{
    /*
    Takes a weapon's index and the inventory slot that it occupies.
    Updates the WEAPON slot in the equipment array, and removes it from the inventory.
    Updates the player's ATTACK stat based on the new weapon's modifier.
    */
    myPlayer.resetAttack();

    if (myPlayer.getWeapon() != -1 && itemIndex != 1)
    {
        myPlayer.removeInventoryAt(inventorySlot);
        myPlayer.addInventory(myPlayer.getWeapon());
    }

    myPlayer.setWeapon(itemIndex);
    cout << "You equip your weapon. Your base ATK increases by +" << myItemCatalog.getModifier(itemIndex) << "." << endl;

    cout << "Your ATK was " << myPlayer.getAttack() << ". ";
    myPlayer.updateAttack(myItemCatalog.getModifier(itemIndex));
    cout << "Your ATK is now " << myPlayer.getAttack() << "." << endl;
}
void Game::useItem(int itemIndex, int inventorySlot)
{
    /*
    Takes an item's index and its location. If the desired item IS a potion, it will consume that potion and update the player's HEALTH.
    If the item's total uses become zero after executing that ("emptying" that item) then it is removed from the inventory and no longer accessible.
    Potions are only usable in a DREAM or in LEVIATHAN.
    */
    if (itemIndex == -1)
    {
        cout << "You don't have an item in that slot!" << endl;
        return;
    }

    myPlayer.updateHealth(myItemCatalog.getModifier(itemIndex));
    if (myPlayer.getHealth() > myPlayer.getMaxHealth())
    {
        myPlayer.setHealth(myPlayer.getMaxHealth());
    }

    myItemCatalog.getUses(itemIndex);

    if (myItemCatalog.getUses(itemIndex) == -2)
    {
        cout << "This isn't edible! Try something else!" << endl;
        return;
    }

    myItemCatalog.updateUses(-1, itemIndex);

    if (myItemCatalog.getUses(itemIndex) == 0)
    {
        cout << myItemCatalog.getName(itemIndex) << " is now empty." << endl;
        myPlayer.removeInventoryAt(inventorySlot);
        return;
    }
    cout << "You drink " << myItemCatalog.getName(itemIndex) << ". Your HEALTH increases by +" << myItemCatalog.getModifier(itemIndex) << "." << endl;
    cout << "You have " << myPlayer.getHealth() << "/" << myPlayer.getMaxHealth() << " health points." << endl;
}

/* Menu Functions
Menu functions comprise the majority of gameplay. It lets the player choose where to go, what they do, and what order they do things in.
*/
void Game::menuMain()
{
    /*
    The main hub of OMEN, the player is able to pick where they go and what they do here. This serves as "step one" for all actions taken in this game.
    It could be considered the first crossroads.
    If a player enters a number or letter that isn't listed in the printed menu, it will output an error message and repeat the selection process.
    Almost each menu item leads to a seperate function, wherein more specific actions are taken.
    */
    char choice;
    while (choice != '7' && myPlayer.getLevel() != 10)
    {
        cout << endl
             << "-------" << endl
             << endl;

        myPlayer.displayBasicStats();
        cout << endl;

        cout << "Pick a number and make your move. Remember, once you enter a Dream, you can't leave without beating the Shade!" << endl;
        cout << "1. Shop at RAVEN MARKET" << endl;
        cout << "2. Visit LEVIATHAN" << endl;
        cout << "3. Enter a DREAM" << endl;
        cout << "4. View detailed stats" << endl;
        cout << "5. View inventory" << endl;
        cout << "6. Equip something." << endl;
        cout << "7. Quit game" << endl;

        cin >> choice;
        cout << endl;

        switch (choice)
        {
        default:
        {
            cout << "That's not possible!" << endl;
            break;
        }

        case '1':
        {
            cout << "A bell chimes as you walk into RAVEN MARKET. ";
            menuMarket();
            break;
        }

        case '2':
        {
            menuArena();
            break;
        }

        case '3':
        {
            cout << "Your head swims as you enter the DREAM. ";
            menuDream();

            if (myPlayer.getCorruption() >= 40)
            {
                dreamCorruptMagic();
            }

            if (myPlayer.getLevel() == 10)
            {
                choice = 7;
            }
            break;
        }

        case '4':
        {
            char exiting;
            while (exiting != 'Y')
            {
                myPlayer.displayStats();
                cout << "Y. Return to main menu" << endl;
                cin >> exiting;
            }
            break;
        }

        case '5':
        {
            char exit;
            genDisplayInventory();
            cout << "Press any key to exit." << endl;
            cin >> exit;
            break;
        }

        case '6':
        {
            equipItem();
            break;
        }

        case '7':
        {
            genSaveFinalReport();

            char quit;
            cout << "Are you sure you want to quit? (Y or N)" << endl;
            cin >> quit;

            if (quit == 'Y')
            {
                cout << "Do you want to view your final data? (Y or N)" << endl;
                char report;

                while (report != 'Y' && report != 'N')
                {
                    cin >> report;

                    if (report == 'Y')
                    {
                        cout << endl;
                        cout << "See you next time!" << endl;
                        return;
                    }
                    else if (report == 'N')
                    {
                        cout << "See you next time!" << endl;
                        return;
                    }
                    else
                    {
                        cout << "That's not possible. Enter Y or N!" << endl;
                        break;
                    }
                }
            }
            if (quit == 'N')
            {
                choice = 0;
                break;
            }
        }
        }
    }
}
void Game::menuArena()
{
    /*
    One of three locations that the player can enter. LEVIATHAN (also called The Arena) allows the player to increase one stat at the expense of another.
    In here, players can also get some subtle hints about what their fate could be...
    */
    char arenaChoice;
    while (arenaChoice != '8')
    {
        cout << "LEVIATHAN is loud, crowded, and untidy. You can hear thoughtful conversations from one corner, and a rowdy argument from another." << endl;
        cout << "A stairway in one corner leads to the Pit; an always-on, free-for-all sparring session. " << endl;
        cout << "Of course, you could just watch others fight. What do you do? Pick a number." << endl;
        cout << "Here, you can get stat boosts, but only temporarily. Equipping an item will undo these changes." << endl;
        cout << "What do you do?" << endl;

        cout << "1. Spar in the Pit (improves ATK, lowers HP)." << endl;
        cout << "2. Join a conversation (improves STAMINA, lowers ATK)." << endl;
        cout << "3. Argue! (improves ATK, lowers DEF)." << endl;
        cout << "4. Watch a fight. (improves DEF, lowers STAMINA)." << endl;
        cout << "5. View detailed stats." << endl;
        cout << "6. Equip an item." << endl;
        cout << "7. Consume a potion." << endl;
        cout << "8. Leave" << endl;

        cout << "Pick a number: ";
        cin >> arenaChoice;
        cout << endl;

        switch (arenaChoice)
        {
        default:
        {
            cout << "That's not possible!" << endl;
            cout << "Returning to main menu..." << endl;
            return;
        }

        case '1':
        {
            if (myPlayer.getHealth() - 1 < 0)
            {
                cout << "You can't afford any more injuries. Try healing up before you enter the pit." << endl;
                break;
            }

            cout << "You leap into the fray. By the end of it, you're bruised and battered, but revitalized." << endl;
            cout << "You've learned from your opponents moves, and they've learned from you." << endl;

            myPlayer.updateAttack(1);
            myPlayer.updateHealth(-1);

            cout << "Your ATK is now " << myPlayer.getAttack() << ". ";
            cout << "You have " << myPlayer.getHealth() << " out of " << myPlayer.getMaxHealth() << " health points." << endl;
            cout << endl
                 << endl;

            break;
        }

        case '2':
        {
            if (myPlayer.getAttack() - 1 < 0)
            {
                cout << "You can't afford to dull your senses now. Try raising your ATK before joining in." << endl;
                break;
            }

            cout << "You hover at the edge of the conversation before diving in." << endl;
            cout << "It's exciting and engaging, to talk with people who really understand this world." << endl;
            cout << "But they have theories about the monsters that unsettle you." << endl;

            myPlayer.updateStamina(1);
            myPlayer.updateAttack(-1);

            cout << "Your STAMINA is now " << myPlayer.getStamina() << ". ";
            cout << "Your ATK is now " << myPlayer.getAttack() << ". ";
            cout << endl
                 << endl;

            break;
        }

        case '3':
        {
            if (myPlayer.getAttack() - 1 < 0)
            {
                cout << "Lowering your defenses would be too risky right now. Boost your DEF and come join later." << endl;
                break;
            }

            cout << "The arguers welcome you in gleefully. The match is raucous, and infuriating, and the adrenaline rush is brilliant." << endl;

            myPlayer.updateStamina(1);
            myPlayer.updateAttack(-1);

            cout << "Your STAMINA is now " << myPlayer.getStamina() << ". ";
            cout << "Your ATK is now " << myPlayer.getAttack() << ". ";
            cout << endl
                 << endl;

            break;
        }

        case '4':
        {
            cout << "Watching the fights is just as useful as participating in them." << endl;
            cout << "You take note of how each fighter moves, and what made the winners come out on top." << endl;
            cout << "All the benefits, none of the injuries." << endl;

            myPlayer.updateDefense(1);
            myPlayer.updateStamina(-1);

            cout << "Your DEF is now " << myPlayer.getDefense() << ". ";
            cout << "Your STAMINA is now " << myPlayer.getStamina() << ". ";
            cout << endl
                 << endl;
            break;
        }

        case '5':
        {
            char exiting;
            while (exiting != 'Y')
            {
                myPlayer.displayStats();
                cout << "Y. Return to menu" << endl;
                cin >> exiting;
            }
            break;
        }

        case '6':
        {
            equipItem();
            break;
        }

        case '7':
        {
            genDisplayInventory();

            int inventorySlot = -1;

            while (inventorySlot != 0)
            {
                cout << "What potion do you want to use? Pick a number." << endl;
                cout << "Pick '0' to cancel." << endl;
                cin >> inventorySlot;
                if (inventorySlot == '0')
                {
                    break;
                }

                int itemIndex = myPlayer.getInventoryAt(inventorySlot - 1);
                useItem(itemIndex, inventorySlot);
            }
            break;
        }

        case '8':
        {
            cout << "You leave LEVIATHAN." << endl;
            return;
        }
        }
    }
    return;
}
void Game::menuDream()
{
    /*
    One of three locations available to visit, DREAMS are a main focus. They describe zones where monsters are; where players can do combat and level up.
    Each turn, it displays the level-appropriate map and lets the player explore and fight in it.
    This zone is special, as players don't have a menu option to leave it. Instead, players exit immediately after fighting (and hopefully defeating) the shade.

    This zone also deals with the map, integrating and calling various map functions and data members.

    If a player runs out of moves (the "timer" variable), or if they lose the battle, then they're banished from the dream without levelling up and must repeat it to progress.

    */
    cout << "Magic pulses around you, pulling at your edges. The monsters haven't noticed you yet. Or maybe they're waiting for you. " << endl;
    cout << "Either way, it's an opportunity you can't pass up." << endl;

    // int timer = 12 + myPlayer.getStamina();
    int timer = 3;
    
    Map dream = dreams[myPlayer.getLevel() - 1];

    if (myPlayer.getTutorial() == true)
    {
        char tooltip;
        cout << "It seems like you haven't fought in a long time. Do you want a crash course in battle mechanics?" << endl;
        cout << "Y. Walk me through this." << endl
             << "N. I don't need it." << endl;

        while (tooltip != 'N')
        {
            cin >> tooltip;

            if (tooltip == 'Y')
            {
                dream.displayMap();
                dream.printMapTutorial();
                tooltip = 'N';
                myPlayer.setTutorial(false);
                break;
            }
            else if (tooltip == 'N')
            {
                myPlayer.setTutorial(false);
                break;
            }
            else if (tooltip != 'Y' && tooltip != 'N')
            {
                cout << "That's not possible. Enter Y or N!" << endl;
                break;
            }
        }
    }

    dream.displayMap();
    char dreamChoice;

    while (dreamChoice != 'h')
    {
        if (timer <= 0)
        {
            myPlayer.updateCorruption(10);
            cout << "You've run out of time. The dream fizzles around you, and you can feel something dark growing inside of you." << endl;
            cout << "You'll have to try this again." << endl;

            char cont;
            cout << "Press any key to continue." << endl;
            cin >> cont;

            return;
        }

        myPlayer.displayBasicStats();
        cout << endl;
        cout << "You have " << timer << " moves left." << endl;
        cout << "What do you do?" << endl;

        cout << "1. Move." << endl;
        cout << "2. View detailed stats." << endl;
        cout << "3. Equip an item." << endl;
        cout << "4. Check your wallet." << endl;
        cout << "5. Consume a potion." << endl;

        cout << "Pick a number: ";
        cin >> dreamChoice;
        cout << endl;

        switch (dreamChoice)
        {
        default:
        {
            cout << "That's not possible!" << endl;
            break;
        }

        case 'h': // dev quick-exit code
        {
            return;
        }

        case '1':
        {
            dream.displayMoves(); // give user a menu of valid moves to pick from

            char move;

            cout << "Input a move: ";
            cin >> move;
            cout << endl;
            bool moving = dream.executeMove(move); // move the player on map based on user input

            if (moving == false)
            {
                timer++;
            }

            if (dream.isShadeLocation() == true)
            {
                int shadeIndex = dreamPrintShade();

                cout << "You face " << myBestiary.getTitle(shadeIndex) << "." << endl;
                cout << myBestiary.getDesc(shadeIndex) << endl
                     << endl;

                bool victory = battleShade();
                if (victory == true)
                {
                    myPlayer.levelUp(1);
                }
                return;
            }

            if (dream.isLootLocation() == true)
            {
                dreamFindLoot();
            }

            if (dream.isMinionLocation() == true)
            {
                int minionIndex = dreamPrintMinion();

                cout << "You face " << myBestiary.getTitle(minionIndex) << "." << endl;
                ;
                cout << myBestiary.getDesc(minionIndex) << endl
                     << endl;

                bool victory = battleMinion();

                dream.resetLocation(dream.getPlayerRowPosition(), dream.getPlayerColPosition());
                if (victory == true)
                {
                    cout << "The adrenaline rush boosts your stamina." << endl;
                    timer += 2;
                }
            }

            dream.displayMap();
            timer--;
            break;
        }
        case '2':
        {
            myPlayer.displayStats();

            char cont;
            cout << "Press any key to continue." << endl;
            cin >> cont;
            break;
        }

        case '3':
        {
            equipItem();

            char cont;
            cout << "Press any key to continue." << endl;
            cin >> cont;
            break;
        }

        case '4':
        {
            myPlayer.displayWallet();
            char money;
            cout << "Press any key to continue." << endl;
            cin >> money;
        }

        case '5':
        {
            genDisplayInventory();

            int inventorySlot = -1;

            while (inventorySlot != 0)
            {
                cout << "What potion do you want to use? Pick a number." << endl;
                cout << "Pick '0' to cancel." << endl;
                cin >> inventorySlot;
                if (inventorySlot == '0')
                {
                    break;
                }

                int itemIndex = myPlayer.getInventoryAt(inventorySlot - 1);
                useItem(itemIndex, inventorySlot);
            }
            break;
        }
        }
    }

    return;
}
void Game::menuMarket()
{
    /*
    This lets the player purchase new items, in order to boost their stats in different ways. There are four actual stores within this main one; each one has its own specific stat that it interacts with.
    Players can also sell inventory items here.
    If the player enters a character not listed in the menu, it will print an error message and repeat the menu and selection process.
    */
    char marketChoice;
    while (marketChoice != '9')
    {
        cout << "The store is dim, but cozy. In the display near the register, there's an array of glittering jewelry. "
             << "Against the wall, there are shelves holding various gemstones and vials. In the back, you can see a display of various weapons." << endl;
        cout << "What section do you browse?" << endl << endl;

        cout << "1. The jewelry (improves DEF)." << endl;
        cout << "2. The weapons (improves ATK)." << endl;
        cout << "3. The gemstones (improves STAMINA)." << endl;
        cout << "4. The vials (improves HP)." << endl;
        cout << "" << endl << "You can also..." << endl << "" << endl;
        cout << "5. Check your wallet." << endl;
        cout << "6. Check your inventory." << endl;
        cout << "7. View detailed stats." << endl;
        cout << "8. Sell something." << endl;
        cout << "9. Leave RAVEN MARKET." << endl << endl;



        cout << "Pick a number: ";
        cin >> marketChoice;
        cout << endl;

        switch (marketChoice)
        {
        default:
        {
            cout << "That's not possible!" << endl
                 << endl;
            break;
        }

        case '1':
        {
            cout << "The jewelry glitters in the dim light." << endl;
            shopDisplayWares(defenseStore);
            break;
        }
        case '2':
        {
            cout << "You approach the display of weaponry and find..." << endl;
            shopDisplayWares(attackStore);
            break;
        }

        case '3':
        {
            cout << "Examining the collection of stones, you see:" << endl;
            shopDisplayWares(staminaStore);
            break;
        }

        case '4':
        {
            cout << "The vials litter the shelves, available in every shape and color you can think of. A few catch your eye." << endl;
            shopDisplayWares(healthStore);
            break;
        }
        case '5':
        {
            myPlayer.displayWallet();
            break;
        }

        case '6':
        {
            genDisplayInventory();

            char cont;
            cout << "Press any key to continue." << endl;
            cin >> cont;
            break;
        }

        case '7':
        {
            char exiting;
            while (exiting != 'Y')
            {
                myPlayer.displayStats();
                cout << "Y. Return to menu" << endl;
                cin >> exiting;
            }
            break;
        }

        case '8':
        {
            shopMakeSale();
            break;
        }

        case '9':
        {
            cout << "You leave the market." << endl;
            return;
        }
        }
    }

    return;
}

/* Shop Functions
Shop functions deal with purchasing and selling items; updating the player's wallet, removing/adding items from store/inventory arrays, etc.
Most of them take in a StoreID value, to indicate which store it needs to access (weapons, jewelry, etc).
*/
int Game::shopPurchaseItem(int storeID, int storeSlot)
{
    /*
    Takes in a specific store, and the location of the desired item in that store.
    It returns an integer so that the function that calls this one (shopDisplayWares) can execute properly.
    If the item is accessible, it will calculate the price and let the player pick whether or not to buy it.
    If they buy it, the player's wallet will be updated, as will their inventory.
    */
    int maxStoreItems = stores[storeID].getMaxWares();

    if (storeSlot == 0)
    {
        return 0;
    }
    if (storeSlot < 0 || storeSlot > maxStoreItems)
    {
        cout << "That's not possible. Pick something else!" << endl;
        return -1;
    }

    int itemIndex = stores[storeID].getItemAt(storeSlot);
    if (itemIndex >= 0)
    {
        itemDisplayDetails(itemIndex);
    }
    else
    {
        cout << "That item isn't available. Pick something else!" << endl;
        return -1;
    }

    int itemPrice = myItemCatalog.findPrice(itemIndex);
    cout << "It costs " << itemPrice << " dollars. ";
    cout << "You have " << myPlayer.getWallet() << " dollars available." << endl
         << endl;

    if (myPlayer.getWallet() < itemPrice)
    {
        cout << "You don't have enough money! Try selling something you no longer need, or fight another Shade." << endl;
        return 0;
    }

    cout << "Do you want to buy it? Y or N" << endl;

    char purchase;
    while (purchase != 'N' || purchase != 'Y')
    {
        cin >> purchase;
        if (purchase == 'N')
        {
            cout << "You put it back." << endl;
            return 0;
        }
        if (purchase == 'Y')
        {
            stores[storeID].removeItemAt(storeSlot);

            cout << "It's been added to your inventory!" << endl;
            myPlayer.updateWallet(-1 * itemPrice);
            int funds = myPlayer.getWallet();
            cout << "You have " << funds << " dollars left." << endl;

            myPlayer.addInventory(itemIndex);

            return 0;
        }
        if (purchase != 'Y' && purchase != 'N')
        {
            cout << "That's not possible. Enter Y or N!" << endl;
            return -1;
        }
    }
    return -1;
}
int Game::shopSellItem(int inventorySlot)
{
    /*
    This works very similarly to shopPurchaseItem. It takes in an inventory slot, where the unwanted item is located.
    The inventory slot is immediately reduced by one so it can be used as an array index (and thus find the item's index).
    If the item exists/can be sold, its sale price (different from its purchase price) will be calculated and that amount will be added to the player's wallet. The item will be removed from their inventory.
    Since only inventory items can be sold, equipped items must be traded out to be sold.
    */

    inventorySlot--;
    int itemIndex = myPlayer.getInventoryAt(inventorySlot);
    if (itemIndex >= 0)
    {
        itemDisplayDetails(itemIndex);
    }
    else
    {
        cout << "That item isn't available. Pick something else!" << endl;
        return -2;
    }

    int itemPrice = myItemCatalog.findSalePrice(itemIndex);
    if (itemPrice == 0)
    {
        itemPrice = 3;
    }

    cout << "This can be sold for " << itemPrice << " dollars. ";
    cout << "You have " << myPlayer.getWallet() << " dollars." << endl
         << endl;

    cout << "Do you want to sell it? (Y or N)" << endl;

    char sale;
    while (sale != 'N' || sale != 'Y')
    {
        cin >> sale;
        if (sale == 'N')
        {
            cout << "Transaction cancelled." << endl;
            return 0;
        }
        if (sale == 'Y')
        {
            myPlayer.removeInventoryAt(inventorySlot);
            cout << "You sell ths item, and earn " << itemPrice << " dollars." << endl;

            myPlayer.updateWallet(itemPrice);
            int funds = myPlayer.getWallet();
            cout << "You have " << funds << " dollars." << endl;

            return 0;
        }
        if (sale != 'Y' && sale != 'N')
        {
            cout << "That's not possible. Enter Y or N!" << endl;
            return -1;
        }
    }
    return -1;
    /*
        takes the index of an item from the player's inventory. removes it from the inventory and calculates the money the player receives. returns that sale price.
    */
}
void Game::shopDisplayMenu(int storeID)
{
    /*
    This displays the items available for sale for a store/category of items. It only outputs available items; there are no empty slots in the stores.
    */
    int maxStoreLength = stores[storeID].getMaxWares();
    bool isEmpty = true;
    for (int slot = 1; slot <= maxStoreLength; slot++)
    {
        int itemIndex = stores[storeID].getItemAt(slot);
        if (itemIndex >= 0)
        {
            cout << slot << ". " << myItemCatalog.getName(itemIndex) << endl;
            isEmpty = false;
        }
    }

    if (isEmpty == true)
    {
        cout << "You've bought everything!" << endl;
        return;
    }

    cout << endl;
}
void Game::shopDisplayWares(int storeID)
{
    /*
    This function displays the items available for purchase in a store, and lets the player select one to purchase.
    The item display and the actual purchasing are both handled by seperate functions.
    */
    int storeSlot = -2;

    while (storeSlot != '0')
    {
        shopDisplayMenu(storeID);

        cout << "0. Leave this area." << endl;
        cout << "What item do you want to look at? Pick a number: ";

        if (storeSlot == 0)
        {
            break;
        }

        cin >> storeSlot;
        cout << endl;

        storeSlot = shopPurchaseItem(storeID, storeSlot);
    }
    cout << "Leaving..." << endl;
}
void Game::shopMakeSale()
{
    /*
    This function works similarly to shopDisplayWares, only with selling things! It displays the player's inventory and lets them select an item to sell.
    Exceptions/erroneous input (an empty slot, etc) is handled by the actual shopSellItem function. Same with displaying the player's inventory (genDisplayInventory).
    */
    int itemSlot = -2;

    while (itemSlot != 0)
    {
        genDisplayInventory();

        cout << "0: Leave this menu." << endl;
        cout << "What item do you want to sell? Pick a number: ";

        cin >> itemSlot;
        cout << endl;

        if (itemSlot == 0)
        {
            cout << "Returning..." << endl;
            return;
        }
        itemSlot = shopSellItem(itemSlot);
    }
}

/* Item Functions
Item functions get various information about desired information from the Item Catalog; the item's name, modifier, etc. It also displays the important information about given items.
*/
int Game::itemGetModAt(int index)
{
    /*
    Takes an item's index and finds its modifier value.
    */
    int itemMod = ItemCatalog().getModifier(index);
    return itemMod;
}
void Game::itemDisplayDetails(int index)
{
    /*
    Takes an item's index. It displays this item's name and description, and then outputs information about what stat it modifies based on its type.
    If the item has a limited amount of uses, that amount of uses will also be printed. Infinite uses (such as for jewelry) are indicated by a "-2".
    */
    string currentName = myItemCatalog.getName(index);
    string currentDesc = myItemCatalog.getDesc(index);
    int currentMod = myItemCatalog.getModifier(index);
    int currentUses = myItemCatalog.getUses(index);
    char currentType = myItemCatalog.getType(index);

    cout << currentName << endl;
    cout << currentDesc << endl;

    if (currentType == 'W')
    {
        cout << "This item boosts your ATK by +" << currentMod << ".";
    }
    if (currentType == 'J')
    {
        cout << "This item boosts your DEF by +" << currentMod << ".";
    }
    if (currentType == 'G')
    {
        cout << "This item boosts your STAMINA by +" << currentMod << ".";
    }
    if (currentType == 'V')
    {
        cout << "This item boosts your HEALTH by +" << currentMod << ".";
    }

    if (currentUses == -2)
    {
        cout << endl;
    }
    else
    {
        cout << " It can be used " << currentUses << " times." << endl;
    }
}
void Game::itemGetDetails()
{
    /*
    The player can select an inventory item and see its information. The getting/printing of that information is handled by a seperate function (itemDisplayDetails).
    */
    int inventorySlot;
    cout << "What item do you want to look at? Pick a number." << endl;
    cin >> inventorySlot;

    int itemIndex = myPlayer.getInventoryAt(inventorySlot - 1);

    itemDisplayDetails(itemIndex);

    return;
}
string Game::itemGetNameAt(int index)
{
    /*
    Takes in an item's index, and returns that item's name.
    */
    string itemName = ItemCatalog().getName(index);
    return itemName;
}

/* Battle Functions
Battle functions are only called when the player encounters a monster, and they determine how each encounter goes.
*/
int Game::battleMain()
{
    /*
    This function is called when the player encounters a monster, either Shade or Minion.
    Uses the player's Attack and Defense stat, in combination with a random number, to calculate the player's power.
    The player's level and a different random number is used to calculate the power of the monster.

    If the monster has a greater power than the player, then the player would lose.
    If the player's power is greater, then they'd win!
    This is found via subtracting the monster's power from the player's.

    Returns an integer. The returned integer's positivity/negativity represents whether or not the player won the battle.
    */
    srand(time(NULL));

    int playerChance = 1 + (rand() % 6);
    int monsterChance = 1 + (rand() % 6);

    int playerAttack = myPlayer.getAttack();
    int playerDefense = myPlayer.getDefense();

    int battleResult = (playerChance * myPlayer.getAttack() * myPlayer.getDefense()) - (monsterChance * myPlayer.getLevel());

    return battleResult;
}
bool Game::battleShade()
{
    /*
    Battles with Shades are special, as the shade requires multiple hits to defeat. The above battle formula is called multiple times, until the shade's health is reduced to zero.
    Each time that the player loses any battle with the shade and is hit by it, they lose some health and gain corruption (see: corruption, in Player class).
    Each time that the player hits the Shade, they reduce their corruption.

    There's an input catch halfway through the battle outputs, so the player can actually read everything that happens without losing their place or missing things.

    Returns a boolean value, determining if the player won or lost.
    */
    int shadeHealth = 1 + myPlayer.getLevel();

    while (shadeHealth > 0)
    {
        int battleResult = battleMain();

        if (battleResult > 0)
        {
            myPlayer.updateCorruption(-10);
            shadeHealth--;

            cout << "You bypass the Shade's defenses and attack!" << endl;
            cout << "It has " << shadeHealth << " HP left." << endl;
        }
        else
        {
            myPlayer.updateHealth(-1);
            myPlayer.updateCorruption(10);

            cout << "The Shade strikes you. Your HP is now " << myPlayer.getHealth() << "." << endl;
            cout << "Something dark brims underneath your magic." << endl;
        }

        char cont;
        cout << "Press any key to continue." << endl;
        cin >> cont;

        if (shadeHealth <= 0)
        {
            cout << "The shade dissolves into dust and light. You've done something good today." << endl;
            return true;
        }

        if (myPlayer.getHealth() <= 0)
        {
            cout << "The shade stands tall as you collapse, injured beyond your limits. You'll try again... after you've healed." << endl;
            myPlayer.updateHealth(1);
            return false;
        }
    }

    return false;
}
bool Game::battleMinion()
{
    /*
    Battles with minions are one-and-done things. Players can either win a battle or lose, and minions are removed from the map after one encounter.
    If the player wins, they reduce their corruption. If they lose, they lose a Health Point and gain corruption.
    */
    int battleResult = battleMain();

    char cont;
    cout << "Press any key to ATTACK. Whether you win or lose, this should be quick." << endl;
    cin >> cont;

    if (battleResult >= 0)
    {
        myPlayer.updateCorruption(-5);
        cout << "You dodge the minion's defenses and attack! With a final forceful blow, it crumbles back into light." << endl;
        return true;
    }
    else
    {
        myPlayer.updateHealth(-1);
        myPlayer.updateCorruption(5);

        cout << "The thing strikes you. You stumble backwards, away from the danger. Your HP is now " << myPlayer.getHealth() << "." << endl;
        cout << "Your magic twists in your grip. You feel... wrong." << endl;
    }

    return false;
}

/* Dream Functinos
Dream functions deal with everything else that is dream-specific, beyond the battles. This includes outputting details about each monster and discovering loot.
*/
void Game::dreamCorruptMagic()
{
    /*
    This runs if the player ever reaches a corruption level beyond 40. Their magic will change to Black Magic, a hidden magic type.
    This doesn't remove previous benefits. It increases the player's maximum health by 1, and fully heals them.
    It also sets their corruption to fifty, putting them at greater risk for the Shade Ending (which could be called the bad ending).
    */

    cout << "Your magic has turned dim and heavy in your hands. You can feel yourself changing, a hollow growing where your magic once had been." << endl;
    cout << "The damage you've gone through has taken your strength, and with it, your power." << endl;
    cout << "The abyss welcomes you. Your magic turns BLACK." << endl;
    cout << endl;

    myPlayer.setCorruption(50);
    myPlayer.setMagic('K');
    myPlayer.updateMaxHealth(1);
    myPlayer.setHealth(myPlayer.getMaxHealth());
}
void Game::dreamFindLoot()
{
    /*
    This determines what kind of loot the player will find after entering a Loot space.
    There are three types; normal, critical, or special.
    Normal loot is just three dollars.
    Special loot is a special kind of item; either weapon, jewelry, potion, or gem. The specific item type is determined by the player's level.
    There is a 20% chance of finding special loot. Each can only ever be found once.

    Critical loot exists between normal and special. There is a 50% chance of finding critical loot (assuming the special item has already been found).
    If the player is in a spot that would have special loot, but they've already found that item, then they'll receive critical loot.
    */
    int criticalLoot = (int)(rand() % 100) + 1;
    int lootAmount = 1;
    char lootContinue;

    if (criticalLoot <= 20)
    {
        cout << "You almost trip over something on the ground. You pick it up:" << endl;
        int level = myPlayer.getLevel();
        int itemIndex = -2;

        if (level <= 3 && myItemCatalog.getVialFound() == false)
        {
            itemIndex = myItemCatalog.getIndex("vial7");
            cout << myItemCatalog.getName(itemIndex) << "." << endl;
            cout << myItemCatalog.getDesc(itemIndex) << endl;
            myPlayer.addInventory(itemIndex);
            myItemCatalog.setVialFound(true);

            genPrintSpecialItem();

            cout << "Press any key to continue." << endl;
            cin >> lootContinue;
            return;
        }
        else if (level <= 3 && myItemCatalog.getVialFound() == true)
        {
            criticalLoot = 21;
        }
        else if (level <= 5)
        {
            itemIndex = myItemCatalog.getIndex("gemstone7");
            cout << myItemCatalog.getName(itemIndex) << "." << endl;
            cout << myItemCatalog.getDesc(itemIndex) << endl;
            myPlayer.addInventory(itemIndex);
            myItemCatalog.setGemstoneFound(true);

            genPrintSpecialItem();

            cout << "Press any key to continue." << endl;
            cin >> lootContinue;
            return;
        }
        else if (level <= 5 && myItemCatalog.getGemstoneFound() == true)
        {
            criticalLoot = 21;
        }
        else if (level <= 7)
        {
            itemIndex = myItemCatalog.getIndex("jewelry7");
            cout << myItemCatalog.getName(itemIndex) << "." << endl;
            cout << myItemCatalog.getDesc(itemIndex) << endl;
            myPlayer.addInventory(itemIndex);
            myItemCatalog.setJewelryFound(true);

            genPrintSpecialItem();

            cout << "Press any key to continue." << endl;
            cin >> lootContinue;
            return;
        }
        else if (level <= 7 && myItemCatalog.getJewelryFound() == true)
        {
            criticalLoot = 21;
        }
        else if (level <= 9)
        {
            itemIndex = myItemCatalog.getIndex("weapon7");
            cout << myItemCatalog.getName(itemIndex) << "." << endl;
            cout << myItemCatalog.getDesc(itemIndex) << endl;
            myPlayer.addInventory(itemIndex);
            myItemCatalog.setWeaponFound(true);

            genPrintSpecialItem();

            cout << "Press any key to continue." << endl;
            cin >> lootContinue;
            return;
        }
        else if (level <= 5 && myItemCatalog.getWeaponFound() == true)
        {
            criticalLoot = 21;
        }
    }

    if (criticalLoot > 20 && criticalLoot <= 50)
    {
        lootAmount = 6;
    }
    else
    {
        lootAmount = 3;
    }

    cout << "There's a card lying near your feet. You pick it up: the outside is boring, and the inside only says:" << endl;
    cout << "   'For you. Good luck.' " << endl;
    cout << "There's no signature, but there are " << lootAmount << " dollars folded up in the card." << endl;
    cout << "You hope that whoever wrote this is still alive. You'd like to thank them for the card." << endl;
    cout << endl;

    myPlayer.updateWallet(lootAmount);
    cout << "You now have " << myPlayer.getWallet() << " dollars." << endl;

    cout << "Press any key to continue." << endl;
    cin >> lootContinue;
}
int Game::dreamPrintMinion()
{
    /*
    This determines what kind of minion the player is facing (based on their level). It then outputs the minion's title and description.
    Returns the index of the minion being fought.
    */
    int level = myPlayer.getLevel();
    string lvl = to_string(level);

    string minionCode = "minion" + lvl;
    int monsterIndex = myBestiary.getIndex(minionCode);

    return monsterIndex;
}
int Game::dreamPrintShade()
{
    /*
    This determines what kind of shade the player is facing (based on their level). It then outputs the shade's title and description.
    Returns the index of the shade being fought.
    */

    int level = myPlayer.getLevel();
    string lvl = to_string(level);

    string shadeCode = "shade" + lvl;
    int monsterIndex = myBestiary.getIndex(shadeCode);

    return monsterIndex;
}
void Game::dreamRandomizeSpawn()
{
    /*
        Spawns in the SHADES (main monsters), MINIONS (secondary monsters), and LOOT, in that order. Shades are given priority as the main combatant; loot is given lowest priority.
        The latter two loops are nested so that it'll spawn the correct amount of minions/loot (since there should be more than one of each present in each map).
    */
    srand(time(NULL));

    int randomRow = 0;
    int randomCol = 0;
    int maximum = myPlayer.getMaxLevel();

    int numMinions = dreams[0].getNumMinions();
    int numLoot = dreams[0].getNumLoot();
    // spawning shades
    for (int mapLevel = 0; mapLevel < maximum; mapLevel++)
    {
        randomRow = 0 + (rand() % 5);
        randomCol = 0 + (rand() % 9);
        dreams[mapLevel].spawnShade(randomRow, randomCol);
    }

    // spawning minions
    for (int mapLevel = 0; mapLevel < maximum; mapLevel++)
    {
        for (int minionCount = 0; minionCount < numMinions; minionCount++)
        {
            randomRow = 0 + (rand() % 5);
            randomCol = 0 + (rand() % 9);
            dreams[mapLevel].spawnMinion(randomRow, randomCol);
        }
    }

    // spawning loot
    for (int mapLevel = 0; mapLevel < maximum; mapLevel++)
    {
        for (int lootCount = 0; lootCount < numLoot; lootCount++)
        {
            randomRow = 0 + (rand() % 5);
            randomCol = 0 + (rand() % 9);
            dreams[mapLevel].spawnLoot(randomRow, randomCol);
        }
    }
}
