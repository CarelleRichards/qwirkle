#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Board.h"
#include "Game.h"
#include "TileBag.h"

class FileHandler {

   public:

    FileHandler(bool testFlag, bool enhancedFlag);
    FileHandler(const FileHandler& other);
    FileHandler(FileHandler&& other);
    ~FileHandler();

    // If the provided file name is valid, the program will try to copy the 
    // file to a vector and create a game from it. If the load is successful, 
    // a pointer to the game will be returned, otherwise an error will display. 
    Game* loadGame(const std::string fileName);

    // If the provided file name is valid, the game will be outputted 
    // to a ".save" file. The file will be overwritten if it already 
    // exists. An error will display if saving was unsuccessful.
    void saveGame(const Game* game, const std::string fileNameInput);

   private:

    // Indicates if game is in test mode. 
    bool testFlag;

    // Indicates if game has enhanced capabilities. 
    bool enhancedFlag;

    // Takes a file vector and tries to create a game from it. The program
    // will check that the vector contains a full set of tiles. It is assumed 
    // everything else in the file is correct. If a game is successfully 
    // made, a pointer will be returned, otherwise an error will display. 
    Game* gameFromVec(const std::vector<std::string> fileVec);

    // Takes a string, creates a hand from it and returns the pointer.
    // An example of valid hand string is, "R1,G3,O2,B3,R2,R1".
    Hand* handFromStr(const std::string handSt);

    // Takes a string, creates a board from it and returns the pointer. 
    // An example of a valid board string is, “B4@B2 ,B6@B3 ,B5@B4”.
    Board* boardFromStr(const std::string boardStr);

    // Takes a string, creates a tile bag from it and returns a pointer.
    // An example of a valid tile bag string is, "Y5,R5,O2".
    TileBag* tileBagFromStr(const std::string playerHandStr);

    // Compare the names of players in the given vector against the
    // name string. If there is a match, this means the player is the
    // current player and their position in the vector will be returned.
    int currPlayerFromStr(const std::vector<Player*> players,
        const std::string nameStr) const;

    // Trim whitespace from start and end of a string.
    std::string trim(const std::string& source);

    // Returns true if file exists with file name input.
    bool fileExists(const std::string fileNameInput);

    // If in test mode, save/load folder is tests, else savedGames.
    std::string makeFilePath(const std::string fileNameInput);

    Player* playerFromStr(const std::string nameStr, 
        const std::string scoreStr, const std::string handStr);
    
    // Takes a string and determines the game mode from it. String must be 
    // 1, 2, 3 or 4. If not one of these, default mode (dual) will be assumed. 
    Mode modeFromStr(const std::string modeInput);
};

#endif  // FILEHANDLER_H