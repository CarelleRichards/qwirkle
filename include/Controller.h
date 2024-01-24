#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <sstream>
#include <string>

#include "FileHandler.h"
#include "Game.h"
#include "Hand.h"
#include "LinkedList.h"
#include "Validator.h"

class Controller {

   public:

    Controller(bool testFlag, bool enhancedFlag);
    Controller(const Controller& other);
    Controller(Controller&& other);
    ~Controller();

    // Used by main() to start the program. Displays a
    // welcome message and continues to the main menu.
    void launchGame();

   private:

    Game* game;
    Validator* validator;
    FileHandler* fileHandler;

    // If exit mode is true, the mainMenu() loop
    // will end and the game will exit safely.
    bool exitMode;

    // When test flag is true, a random seed is set when the
    // game shuffles the tiles to ensure consistent randomness. 
    bool testFlag;

    // When enhanced flag is true, all 
    // enhanced capabilities will be enabled. 
    bool enhancedFlag;

    // Displays the main menu and asks the user
    // to make a selection by typing a number.
    void mainMenu();

    // When enhanced flag is true, the user will have the 
    // option to choose from regular and enhanced game modes.
    // (1) Player vs. computer (enhancement)
    // (2) Two players (regular)
    // (3) Three players (enhancement)
    // (4) Four players (enhancement)
    void newGameMenu();

    // Asks for the names and makes a new game.
    void newGame(Mode mode);

    // Used in newGame(). Assigns name input to given string pointer.
    void playerNamePrompt(std::string* nameInput,
        const std::vector<Player*>* players);

    // Asks the user for a relative path to a saved game file.
    // If file is valid, the game is loaded and gameplay continues.
    // Otherwise, the user is taken back to the main menu.
    void loadGame();

    // Displays details of each student in the group.
    void credits();

    // Displays a goodbye message and quits safely.
    void exitGame();

    // During baseGameplay(), players will takeTurn() placing tiles
    // from their hand onto the board, until the game is complete.
    void baseGameplay();
    void takeTurn();

    // Tries to skip the current player's turn,
    // the input status is set to true if successful.
    void skipTurn(bool* inputStatus);

    // Takes a player and displays their score.
    void playerScores();

    // Called during takeTurn(). Asks the user to
    // enter a command, validates it and processes it.
    // (1) <colour><shape> at <row><col>
    // (2) replace <colour><shape>
    // (3) save <filename>
    // (4) EOF character ^D
    // (5) skip
    void turnPrompt();

    // Takes the user command and tries to place a tile,
    // the input status is set to true if successful.
    void placeTile(std::string commandInput, bool* inputStatus);

    // Takes the user command and tries to replace a tile,
    // the input status is set to true if successful.
    void replaceTile(std::string commandInput, bool* inputStatus);

    // Displays the end game message, scores,
    // winner name and safely quits the program.
    void endGame();

    // Takes the user command and tries and tries to save the
    // current game. If sucessfully saved, gameplay continues.
    void saveGame(const std::string fileName);

    // Promts the user to enter an input and
    // assigns it to the given string pointer.
    void inputPrompt(std::string* input);

    // Returns true if game is in exist mode.
    bool isExitMode() const;

    // Displays the name of the winner(s). Used in endGame().
    void winners() const;
};

#endif  // CONTROLLER_H