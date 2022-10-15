----------------------------------------------------
COMPILING AND RUNNING THE PROGRAM
----------------------------------------
Compilation Command: 
g++ -std=c++11 OmenDriver.cpp Game.cpp Map.cpp Player.cpp Store.cpp Helper.cpp Bestiary.cpp ItemCatalog.cpp -o OmenGame

Run Command: 
./OmenGame

----------------------------------------------------
DEPENDENCIES
----------------------------------------
The following files MUST be present in the directory (along with the cpp files) for the game to compile and run.

Bestiary.h
Game.h
Helper.h
ItemCatalog.h
Map.h
Player.h
Store.h
items.txt
monsters.txt

----------------------------------------------------
ABOUT "OMEN" (PROJECT 3)
----------------------------------------
"OMEN" is a game set in a fantasy world, where the player has been cursed with magic. 
They must fight various monsters throughout play in order to progress and ultimately escape their curse.
Players can connect with a magical community in a secretive arena, and buy enchanted objects with money scrounged from fights and the sale of old things.
The game operates based on a numeric menu system; players are given numbered lists of things to do or items to interact with. 
Players can enter a number to select and activate that option.

It uses the pre-made Map class to print out battle maps in the relevant locations.