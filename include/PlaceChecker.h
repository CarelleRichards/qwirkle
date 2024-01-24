#ifndef PLACECHECKER_H
#define PLACECHECKER_H

#include "Board.h"
#include "Player.h"

class PlaceChecker {

   public:
    
    PlaceChecker();
    PlaceChecker(const PlaceChecker& other);
    PlaceChecker(PlaceChecker&& other);
    ~PlaceChecker();

    // Takes the board, current player, placed tile and position and returns 
    // true if the placement of the tile is legal according to the rules.
    // (1) Tiles must share one colour or shape attribute.
    // (2) Tiles must be placed in the same line.
    // (3) A line can never be longer than six tiles.
    // (4) There cannot be duplicate tiles in a line.
    // (5) The tile must be in the current player's hand.
    bool checkPlace(Board* board, Player* player, 
        Tile* placedTile, char row, int col);

   private:

    // Records tiles in the row of the placed tile.
    std::vector<Tile*> getRowTiles(Board* board, char row, int col);

    // Records tiles in the col of the placed tile. 
    std::vector<Tile*> getColTiles(Board* board, char row, int col);

    // Takes a vector of row/column tiles and returns
    // true if all their colours or shapes match.
    bool coloursOrShapesMatch(std::vector<Tile*> axis, Tile* placedTile);

    // Returns true if a tile already exists on the 
    // board at the position of the tile placed. 
    bool tileAtLocation(Board* board, char row, int col);

    // Returns true if the tile placed is in the player's hand.
    bool playerHasTile(Player* player, Tile* placedTile);

    // Returns true if tile has been placed in a line.
    bool tilesInLine(Board* board, std::vector<Tile*> rowTiles, 
        std::vector<Tile*> colTiles);

    // Returns true if there are duplicate tiles in a line.
    bool duplicateTiles(std::vector<Tile*> axis, Tile* placedTile);
};

#endif  // PLACECHECKER_H
