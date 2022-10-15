#include "Map.h"

using namespace std; 

Map::Map()
{
    resetMap();
}

int Map::getNumMinions()
{
    return numMinions;
}
int Map::getNumLoot()
{
    return numLoot;
}

void Map::resetMap() 
{
    /* 
    This function empties the map, resetting it.
    It initializes all values in position arrays to "-1", indicating an empty space.
    It also results the "count" variables; the tallies of all the non-player values that could be spawned in the map.
    */
    playerPosition[0] = 0; 
    playerPosition[1] = 0;

    shadePosition[0] = -1;
    shadePosition[1] = -1;

    minionCount = 0;
    lootCount = 0;
    shadePresent = false;

    for (int i = 0; i < numMinions; i++) {
        minionPositions[i][0] = -1;
        minionPositions[i][1] = -1;
    }

    for (int i = 0; i < numLoot; i++) {
        lootPositions[i][0] = -1;
        lootPositions[i][1] = -1;
    }

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            mapData[i][j] = '-';
        }
    }
}

void Map::resetLocation(int row, int column)
{
    mapData[row][column] = '-';
}

int Map::getPlayerRowPosition() {
// return player's row position
    return playerPosition[0];
}

int Map::getPlayerColPosition() {
// return player's column position
    return playerPosition[1];
}

int Map::getMinionCount() {
    return minionCount;
}

int Map::getLootCount() {
    return lootCount;
}

// set player's row position to parameter row
void Map::setPlayerRowPosition(int row) {
    playerPosition[0] = row;
}

// set player's column position to parameter row
void Map::setPlayerColPosition(int col) {
    playerPosition[1] = col;
}

void Map::setMinionCount(int count) {
    minionCount = count;
}

void Map::setLootCount(int count) {
    lootCount = count;
}

/* add Hacker to map
 * Parameters: where to spawn Hacker -- row (int), col (int)
 * Return: (bool) false if no more space in hackerPositions array
 *                      or if (row, col) is an invalid position
 *                      or if (row, col) is already populated; else true
 */
bool Map::spawnLoot(int row, int col) {
    // out of map bounds
    if (!(row >= 0 && row < num_rows && col >= 0 && col < num_cols)) {
        return false;
    }

    if (lootCount >= numLoot) {
        return false;
    }

    // location must be blank to spawn
    if (mapData[row][col] != '-') {
        return false;
    }

    if (lootPositions[lootCount][0] == -1 && lootPositions[lootCount][1] == -1) {
        lootPositions[lootCount][0] = row;
        lootPositions[lootCount][1] = col;
        mapData[row][col] = 'L';
        lootCount++;
        return true;
    }

    return false;
}

/* add NPC to map
 * Parameters: where to spawn NPC -- row (int), col (int)
 * Return: (bool) false if no more space in npcPositions array
 *                      or if (row, col) is an invalid position
 *                      or if (row, col) is already populated; else true
 */
bool Map::spawnMinion(int row, int col) {
    // out of map bounds
    if (!(row >= 0 && row < num_rows && col >= 0 && col < num_cols)) {
        return false;
    }

    if (minionCount >= numMinions) {
        return false;
    }

    // location must be blank to spawn
    if (mapData[row][col] != '-') {
        return false;
    }

    if (minionPositions[minionCount][0] == -1 && minionPositions[minionCount][1] == -1) {
        minionPositions[minionCount][0] = row;
        minionPositions[minionCount][1] = col;
        mapData[row][col] = 'M';
        minionCount++;
        return true;
    }

    return false;
}

/* add Shade to map
 * Parameters: where to spawn Shade -- row (int), col (int)
 * Return: (bool) false if (row, col) is an invalid location
 *                      or if (row, col) is already populated
 *                      or if there is a Sgade already on the map; else true
 */
bool Map::spawnShade(int row, int col) {
    // out of map bounds
    if (!(row >= 0 && row < num_rows && col >= 0 && col < num_cols)) {
        return false;
    }

    // location must be blank to spawn
    if (mapData[row][col] != '-') {
        return false;
    }

    if (shadePresent) {
        return false;
    }

    if (shadePosition[0] == -1 && shadePosition[1] == -1) {
        shadePosition[0] = row;
        shadePosition[1] = col;
        mapData[row][col] = 'S';
        shadePresent = true;
        return true;
    }

    return false;
}

// return true if x, y position has a Shade there
bool Map::isShadeLocation(){
    return shadePosition[0] == playerPosition[0] && shadePosition[1] == playerPosition[1];
}

// return true if x, y position has an Minion there
bool Map::isMinionLocation(){
    for(int i = 0; i < numMinions; i++){
        if(minionPositions[i][0] == playerPosition[0] && minionPositions[i][1] == playerPosition[1]){
            return true; 
        }
    }
    return false; 
}

// return true if x, y position has loot there
bool Map::isLootLocation() {
    for(int i = 0; i < numLoot; i++){
        if(lootPositions[i][0] == playerPosition[0] && lootPositions[i][1] == playerPosition[1]){
            return true; 
        }
    }
    return false; 
}

/*
 * This function prints a menu of valid moves based on playerPosition
 * Parameters: none
 * Return: nothing (void)
 */
void Map::displayMoves() // keep
{
    cout << endl << "Valid moves are: " << endl; 

    if(!(playerPosition[0] == 0)){
        cout << "w (Up)" << endl;
    }
    if(!(playerPosition[0] == (num_rows - 1))){
        cout << "s (Down)" << endl; 
    }
    if(!(playerPosition[1] == 0)){
        cout << "a (Left)" << endl; 
    }
    if(!(playerPosition[1] == (num_cols - 1))){
        cout << "d (Right)" << endl; 
    }
}

/*
 * This function takes in user input
 * and updates playerPosition on the map.
 * Parameters: move (char) -- 'w' (up), 'a' (left), 's' (down), 'd' (right)
 * Return: (bool) if move is valid, then true, else false
 */
bool Map::executeMove(char move){
    // if user inputs w, move up if it is an allowed move
    if(!(playerPosition[0] == 0) && (mapHelper.toLower(move) == 'w')){
        playerPosition[0] -= 1;
        return true; 
    }
    // if user inputs s, move down if it is an allowed move
    else if(!(playerPosition[0] == (num_rows - 1))&& (mapHelper.toLower(move) == 's')){
        playerPosition[0] += 1;
       return true; 
    }
    // if user inputs a, move left if it is an allowed move
    else if(!(playerPosition[1] == 0)&& (mapHelper.toLower(move) == 'a')){
        playerPosition[1] -= 1;
        return true; 
    }
    // if user inputs d, move right if it is an allowed move
    else if(!(playerPosition[1] == (num_cols - 1))&& (mapHelper.toLower(move) == 'd')){
        playerPosition[1] += 1;
        return true; 
    }
    else{
        cout << "The abyss stretches before you, hungry. You'd better not go that way." << endl;
        return false; 
    }
}

/*
 * This function prints a 2D map in the terminal.
 * Parameters: none
 * Return: nothing (void)
 */
void Map::printMapTutorial()
{
    cout << endl << "This is a birds-eye view of the Dream that you're in. Dashes represent empty areas." << endl;
    cout << "The 'X' on the map shows where you are." << endl;
    cout << "The 'S' on the map shows where THE SHADE is." << endl;
    cout << "The 'M' on the map shows where the Shade's MINIONS are." << endl;
    cout << "There are gifts hidden throughout DREAMS by past Harbingers. It's a tradition practiced by some Harbingers: they'll leave something behind to show that once, they were there. A miniscule kind of legacy." << endl;
    cout << "If you cover a lot of ground, you might find something special!" << endl;
    cout << endl;
}

void Map::displayMap() {
    cout << endl;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (playerPosition[0] == i && playerPosition[1] == j) {
                cout << "X";
            } else if (mapData[i][j] == 'L') {  // hides loot from the map
                cout << "-";
            }
            else {
                cout << mapData[i][j];
            }
        }
        cout << endl;
    }
}

// returns true if there is already a Shade on the map
bool Map::isShadePresent() {
    return shadePresent;
}
