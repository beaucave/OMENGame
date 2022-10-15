#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <iostream>
#include "Helper.h"

using namespace std; 

class Map
{
     private:
          static const int num_rows = 5;
          static const int num_cols = 9;
          static const int numMinions = 2;
          static const int numLoot = 3;

          int playerPosition[2];
          int shadePosition[2];
          int minionPositions[numMinions][2];
          int lootPositions[numLoot][2];
          char mapData[num_rows][num_cols];

          int playerStamina = 1;

          int minionCount;
          int lootCount;
          bool shadePresent;

          Helper mapHelper;

     public :
          Map();

          void resetMap();
          void resetLocation(int row, int column);

          int getNumMinions();
          int getNumLoot();
          
          // Shade Functions
          bool spawnShade(int, int);
          bool isShadeLocation();
          bool isShadePresent();

          // Minion Functions
          int getMinionCount();
          void setMinionCount(int);
          bool spawnMinion(int, int);
          bool isMinionLocation();

          // Treasure Functions
          int getLootCount();
          void setLootCount(int);
          bool spawnLoot(int, int);
          bool isLootLocation();

          // Player Functions
          int getPlayerRowPosition();
          int getPlayerColPosition();
          int getPlayerStamina();
          void setPlayerRowPosition(int);
          void setPlayerColPosition(int);

          // Movement Functions
          void printMapTutorial();
          void displayMap();
          void displayMoves();  
          bool executeMove(char);

};
 
#endif