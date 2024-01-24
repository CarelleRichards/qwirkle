#ifndef BOARD_H
#define BOARD_H

#include <exception>
#include <iostream>
#include <utility>
#include <vector>

#include "Tile.h"

class Board {

   public:

    // Constructor for game with empty board.
    Board();

    Board(const Board& other);
    Board(Board&& other);
    ~Board();

    // Prints the entire board vector.
    void printBoard() const;

    // Takes a tile and adds it at a given
    // row (A-Z) and col (0-25) position.
    void addTileAtPos(Tile* tile, char row, int col);

    // Takes a row (A-Z) and col (0-25) and returns
    // the tile in that position in the board vector.
    Tile* getTileAtPos(char row, int col) const;

    // Returns true if board has no tiles.
    bool isEmpty() const;

    // Returns the number of tiles in the board vector.
    int getLength() const;

    // Takes a string array and adds the tiles from the board
    // to it. The tiles will be added to the array starting 
    // at the given index. Used for checkTiles() in game.
    void addToArray(std::string tilesArray[], int* i);

    // Returns the 2D board vector.
    std::vector<std::vector<Tile*> > getBoardVector() const;

    // Returns the min and max index values for
    // the rows and cols in the board vector.
    int getMinCol() const;
    int getMaxCol() const;
    int getMinRow() const;
    int getMaxRow() const;
    char getMinRowChar() const;
    char getMaxRowChar() const;

    // Returns the board as a string.
    std::string getAsStr();

    // Takes a row (A-Z) and col (0-25) 
    // and delete the tile at that position.
    void deleteAtPos(char row, int col);

   private:
   
    // Defines the min and max index values for
    // the rows and cols in the board vector.
    const static int minCol = 0;
    const static int maxCol = 25;
    const static int minRow = 0;
    const static int maxRow = 25;
    const static char minRowChar = (char)('A' + minRow);
    const static char maxRowChar = (char)('A' + maxRow);

    // Stores the number of tiles on the board.
    // This gets updated during addTileAtPos().
    int length;

    // A 2D vector of tiles. The board is a fixed size of 26 x 26.
    std::vector<std::vector<Tile*> > boardVector;
};

#endif  // BOARD_H