#include "../include/PlaceChecker.h"

PlaceChecker::PlaceChecker() {}

PlaceChecker::PlaceChecker(const PlaceChecker& other) {}

PlaceChecker::PlaceChecker(PlaceChecker&& other) {}

PlaceChecker::~PlaceChecker() {}

bool PlaceChecker::checkPlace(Board* board, Player* player, 
    Tile* placedTile, char row, int col) {
    
    // Record tiles in col and row of placed tile. 
    std::vector<Tile*> rowTiles = getRowTiles(board, row, col);
    std::vector<Tile*> colTiles = getColTiles(board, row, col);
    
    bool isLegal = true;

    // Tile must be in the player's hand.
    if (!playerHasTile(player, placedTile)) {
        isLegal = false;
        
    // Tile can't be placed at a location of another tile on the board.
    } else if (tileAtLocation(board, row, col)) {
        isLegal = false;
        
    // Tiles must be placed in the same line.
    } else if (!tilesInLine(board, rowTiles, colTiles)) {
        isLegal = false;

    // The rest of the checks ensure a line cannot be > 6 tiles.  

    // Tiles must share one colour or shape attribute.
    } else if (!coloursOrShapesMatch(rowTiles, placedTile) || 
        !coloursOrShapesMatch(colTiles, placedTile)) {
        isLegal = false;

    // There cannot be duplicate tiles in a line.
    } else if (duplicateTiles(rowTiles, placedTile) || 
        duplicateTiles(colTiles, placedTile)) {
        isLegal = false;
    }
    return isLegal;
}

std::vector<Tile*> PlaceChecker::getRowTiles(Board* board, char row, int col) {
    std::vector<Tile*> rowTiles;

    // Add tiles below tile placed.
    int currRow = row + 1;
    char max = board->getMaxRowChar();
    while (currRow <= max && board->getTileAtPos(currRow, col) != nullptr) {
        rowTiles.push_back(board->getTileAtPos(currRow, col));
        currRow++;
    }

    // Add tiles above tile placed.
    currRow = row - 1;
    char min = board->getMinRowChar();
    while (currRow >= min && board->getTileAtPos(currRow, col) != nullptr) {
        rowTiles.push_back(board->getTileAtPos(currRow, col));
        currRow--;
    }
    return rowTiles;
}

std::vector<Tile*> PlaceChecker::getColTiles(Board* board, char row, int col) {
    std::vector<Tile*> colTiles;

    // Add tiles right of tile placed.
    int currCol = col + 1;
    int max = board->getMaxCol();
    while (currCol <= max && board->getTileAtPos(row, currCol) != nullptr) {
        colTiles.push_back(board->getTileAtPos(row, currCol));
        currCol++;
    }

    // Add tiles to left of tile placed.
    currCol = col - 1;
    int min = board->getMinCol();
    while (currCol >= min && board->getTileAtPos(row, currCol) != nullptr) {
        colTiles.push_back(board->getTileAtPos(row, currCol));
        colTiles.push_back(board->getTileAtPos(row, currCol));
        currCol--;
    }
    return colTiles;
}

bool PlaceChecker::duplicateTiles(std::vector<Tile*> axis, Tile* placedTile) {
    bool duplicateTiles = false;
    for (Tile* tile : axis) {
        if (tile->colour == placedTile->colour && 
            tile->shape == placedTile->shape) {
            duplicateTiles = true;
        }
    }
    return duplicateTiles;
}

bool PlaceChecker::tilesInLine(Board* board, 
    std::vector<Tile*> rowTiles, std::vector<Tile*> colTiles) {

    bool tilesInLine = board->isEmpty() || 
        rowTiles.size() != 0 || colTiles.size() != 0;
    return tilesInLine;
}

bool PlaceChecker::playerHasTile(Player* player, Tile* placedTile) {
    bool playerHasTile = player->getHand()->containsTile(placedTile);
    return playerHasTile;
}

bool PlaceChecker::coloursOrShapesMatch(std::vector<Tile*> axis, 
    Tile* placedTile) {

    bool shapesMatch = true;
    bool coloursMatch = true;

    // For each tile in row/col axis. 
    for (Tile* tile : axis) {

        // Check of colour or shape matches placed tile.
        if (tile->colour != placedTile->colour) {
            coloursMatch = false;
        }
        if (tile->shape != placedTile->shape) {
            shapesMatch = false;
        }
    }
    bool coloursOrShapesMatch = shapesMatch || coloursMatch;
    return coloursOrShapesMatch;
}

bool PlaceChecker::tileAtLocation(Board* board, char row, int col) {
    bool tileAtLocation = board->getTileAtPos(row, col) != nullptr;
    return tileAtLocation;
}