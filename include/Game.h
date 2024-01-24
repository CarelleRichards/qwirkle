#ifndef GAME_H
#define GAME_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "Board.h"
#include "Hand.h"
#include "Player.h"
#include "ScoreCalculator.h"
#include "PlaceChecker.h"
#include "TileBag.h"

// Defines the game mode.
// (1) Player vs. computer (enhancement)
// (2) Two players (regular)
// (3) Three players (enhancement)
// (4) Four players (enhancement)
enum Mode { single = 1, dual = 2, triple = 3, quad = 4 };

class Game {

   public:

    // Constructor for creating a game with no data. After calling
    // this, you must use loadGame() or newGame() to add the data.
    // The test flag will be passed from main() and set accordingly.
    Game(bool testFlag, bool enhancedFlag);

    Game(const Game& other);
    Game(Game&& other);
    ~Game();

    // To be used after Game() when loading a game from a file. Takes 
    // a vector of players, a tile bag, board and position of current 
    // player in vector. Will return true if game has been loaded. 
    bool loadGame(std::vector<Player*> players, Board* board,
        TileBag* tileBag, int currPlayer, Mode mode);

    // Takes a vector of players. The correct number of players 
    // for the intended game mode must be contained in the vector. 
    void newGame(std::vector<Player*> players, Mode mode);

    // Returns the current player.
    Player* getCurrPlayer() const;

    // Returns the board.
    Board* getBoard() const;

    // Returns the tile bag.
    TileBag* getTileBag() const;

    // Returns the name of the player with the highest score.
    // Multiple player names will be returned if there is a tie. 
    std::vector<std::string> getWinners();

    //  Returns true if game has ended. A game is complete when:
    // (1) The tile bag is empty and one player has an empty hand.
    // (2) Or both players have skipped their turn consecutively.
    bool isComplete();

    // Takes a tile, row (A-Z) and col (0-25). Returns true if the
    // tile has been placed from the current player's hand, their
    // score has been updated and isPlaceLegal() is also true.
    bool placeTile(Tile* tile, char row, int col);

    // Used in placeTile() to commit to placing 
    // a tile if all conditions are satisfied. 
    void commitPlaceTile(Tile* tile, char row, int col) ;

    // Takes a tile and returns true if the tile has been replaced from
    // the current player's hand and isReplaceLegal() is also true.
    bool replaceTile(Tile* tile);

    // Toggles to the next player's turn. The current player will not score.
    // The game will be set to complete if all players have skipped in a row.
    void skipTurn();

    // Returns true if both players have tiles in
    // their hands and the tile bag is empty.
    bool isSkipAvailable();

    // Returns the vector of players.
    std::vector<Player*> getPlayers() const;

    // Returns the game mode.
    Mode getMode() const;

    // Finds the best move for the current player and takes their turn.
    // This is used in the single game mode when its the computer's turn. 
    void takeTurnForPlayer();

    // Finds the best tile for the current player to place. 
    // If successful, places the tile and returns true. 
    bool placeForPlayer();

    // Find the best tile for the current player to replace. 
    // If successful, replaces the tile and returns true. 
    bool replaceForPlayer();

   private:

    Board* board;
    TileBag* tileBag;
    std::vector<Player*> players;

    // For checking that a tile placement is legal during placeTile().
    PlaceChecker* placeChecker;

    // See Mode enum at for more info.
    Mode mode;

    // Stores the position of the current
    // player in the players vector. 
    int currPlayer;

    // For calculating the current player's score in placeTile().
    ScoreCalculator* scoreCalculator;

    // Defines the maximum number of tiles allowed in game.
    const static int maxTilesInGame = 72;

    // When test flag is true, a random seed is set in 
    // shuffleTileBag() to ensure consistent randomness. 
    bool testFlag;

    // When enhanced flag is true, all 
    // enhanced capabilities will be enabled.
    bool enhancedFlag;

    // This is set to true if the tile bag is empty and one player has no
    // tiles in their hand or both players skipped their turn consecutively.
    bool gameComplete;

    // Records how many players have skipped their turn in a row. 
    int skipsInRow;

    // Used after a player completes their turn to pass 
    // the turn to the next player in the players array. 
    void nextPlayerTurn();

    // Take a tile and returns true if replace is
    // legal according to the rules, otherwise false.
    // (1) The tile must be in the current player’s hand.
    // (2) The tile bag must have tiles in it.
    bool isReplaceLegal(Tile* tile) const;

    // Takes a tile, row (A-Z) and col (0-25) and returns true 
    // if the placement of the tile is legal according to the rules.
    // (1) Tiles must share one colour or shape attribute.
    // (2) Tiles must be placed in the same line.
    // (3) A line can never be longer than six tiles.
    // (4) There cannot be duplicate tiles in a line.
    // (5) The tile must be in the current player's hand.
    bool isPlaceLegal(Tile* tile, char row, int col) const;

    // Takes a vector of players, a board and tile bag and
    // returns true if there is a correct set of tiles.
    bool checkTiles(std::vector<Player*> players, 
        Board* board, TileBag* tileBag);

    // Takes two string arrays and compares the values,
    // returns true if identical. Used in checkTiles().
    bool arraysEqual(std::string array1[], std::string array2[]);

    // Takes a string array and adds every tile
    // a game should have. Used in checkTiles().
    void addToArray(std::string expectedTilesArray[]);

    // Take the position of a placed tile 
    // and returns the score for that move. 
    int getScore(char row, int col);
};

#endif  // GAME_H