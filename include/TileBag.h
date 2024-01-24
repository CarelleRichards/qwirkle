#ifndef TILEBAG_H
#define TILEBAG_H

#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <utility>

#include "Hand.h"
#include "LinkedList.h"

class TileBag {

   public:

    // Constructor for creating an empty tile bag.
    // If the tile bag is for a new game, you must follow
    // with newGameTileBag(). If the tile bag is for a
    // loaded  game, you must add all tiles with addTile().
    TileBag();

    TileBag(const TileBag& other);
    TileBag(TileBag&& other);
    ~TileBag();

    // Returns the total titles.
    int getLength() const;

    // Returns true if getLength() is 0.
    bool isEmpty();

    // Fills the tile bag with 72 tiles, in
    // 6 colors and 6 shapes and 2 of each type.
    void fillTileBag();

    // Shuffles the tiles in the tile bag to make a random inital
    // order for a new game. If test flag is true, a random seed
    // is set to ensure consistent randomness of the tile bag.
    void shuffleTileBag(bool testFlag);

    // Takes a tile and adds it to the end.
    void addTile(Tile* tile);

    // Takes a player's hands and fills it with up to 6 tiles
    // from the tile bag. By taking the hand, the contents
    // of the tile bag is never displayed to the users.
    void fillHand(Hand* hand);

    // Takes a string array and adds the tiles from the tile bag
    // to it. The tiles will be added to the array starting
    // the given index. Used for checkTiles() in game.
    void addToArray(std::string tilesArray[], int* i);

    // Returns the tile bag as a string.
    std::string getAsStr();

    // To be used after the constructor when the tile bag is for a new
    // game. Uses fillTileBag() and shuffleTileBag() to generate the
    // tiles and order of the tile bag. If test flag is true, a random
    // seed is set to ensure consistent randomness of the tile bag.
    void newGameTileBag(bool testFlag);

   private:
   
    LinkedList* tileBagList;
};

#endif  // TILEBAG_H