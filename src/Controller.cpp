#include "../include/Controller.h"

Controller::Controller(bool testFlag, bool enhancedFlag) {
    this->game = nullptr;
    this->validator = new Validator();
    this->fileHandler = new FileHandler(testFlag, enhancedFlag);
    this->exitMode = false;
    this->testFlag = testFlag;
    this->enhancedFlag = enhancedFlag;
}

Controller::Controller(const Controller& other) {   
    if (other.game != nullptr) {
        this->game = new Game(*other.game);
    } else {
        this->game = nullptr;
    }    
    this->validator = new Validator(*other.validator);
    this->fileHandler = new FileHandler(*other.fileHandler);
    this->testFlag = other.testFlag;
    this->enhancedFlag = other.enhancedFlag;
    this->exitMode = other.exitMode;
}

Controller::Controller(Controller&& other) {
    this->game = other.game;
    this->validator = other.validator;
    this->fileHandler = other.fileHandler;
    this->testFlag = other.testFlag;
    this->enhancedFlag = other.enhancedFlag;
    this->exitMode  = other.exitMode;
    other.game = nullptr;
    other.validator = nullptr;
    other.fileHandler = nullptr;
    other.testFlag = false;
    other.enhancedFlag = false;
    other.exitMode = false;
}

Controller::~Controller() {
    if (this->game != nullptr) {
        delete this->game;
        this->game = nullptr;
    }
    delete this->validator;
    this->validator = nullptr;
    delete this->fileHandler;
    this->fileHandler = nullptr;
}

void Controller::launchGame() {

    // Program shows a message and continues to the main menu. 
    std::cout << std::endl;
    std::cout << "Welcome to Qwirkle" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << std::endl;
    mainMenu();
}

void Controller::mainMenu() {
    while (!this->isExitMode()) {

        // The main menu shows the options of the program.
        std::cout << "Menu" << std::endl;
        std::cout << "----" << std::endl;
        std::cout << std::endl;
        std::cout << "1. New game" << std::endl;
        std::cout << "2. Load game" << std::endl;
        std::cout << "3. Credits (show student information)" << std::endl;
        std::cout << "4. Quit" << std::endl;

        // User selects an option by typing a number. 
        std::string menuInput = "";
        inputPrompt(&menuInput);

        if (menuInput == "1") {
            this->enhancedFlag ? newGameMenu() : newGame(dual);
        } else if (menuInput == "2") {
            loadGame();
        } else if (menuInput == "3") {
            credits();
        } else if (menuInput == "4" || std::cin.eof()) {
            exitGame();
        } else if (this->enhancedFlag && menuInput == "Help!") {
            std::cout << "Select a menu option by typing a number " 
                         "(1 - 4) or enter ^D to quit." << std::endl;
            std::cout << std::endl;
        } else {
            std::cout << "Select a valid menu option!" << std::endl;
            std::cout << std::endl;
        }
    }
}


void Controller::newGameMenu() {
    bool goBack = false;
    while (!this->isExitMode() && !goBack) {

        // The new game menu shows the game mode options.
        std::cout << "New game" << std::endl;
        std::cout << "--------" << std::endl;
        std::cout << std::endl;
        std::cout << "1. Player vs. computer" << std::endl;
        std::cout << "2. Two players" << std::endl;
        std::cout << "3. Three players" << std::endl;
        std::cout << "4. Four players" << std::endl;
        std::cout << "5. Go back" << std::endl;

        // User selects an option by typing a number. 
        std::string menuInput = "";
        inputPrompt(&menuInput);

        if (menuInput == "1") {
            newGame(single);
        } else if (menuInput == "2") {
            newGame(dual);
        } else if (menuInput == "3") {
            newGame(triple);
        } else if (menuInput == "4") {
            newGame(quad);
        } else if (menuInput == "5") {
            goBack = true;
        } else if (menuInput == "Help!") {
            std::cout << "Select a menu option by typing a number "
                         "(1 - 5) or enter ^D to quit." << std::endl;
            std::cout << std::endl;
        } else if (std::cin.eof()) {
            exitGame();
        } else {
            std::cout << "Select a valid menu option!" << std::endl;
            std::cout << std::endl;
        }
    }
}

void Controller::newGame(Mode mode) {

    // Print a message for starting a new game.
    std::cout << "Starting a new game" << std::endl;
    std::cout << std::endl;

    // Ask for player names, add to vector if valid.
    std::vector<Player*> players;
    int playerNum = 1;
    while (!this->exitMode && playerNum <= mode) {
        std::cout << "Enter a name for player " << playerNum 
                  << " (uppercase characters only)" << std::endl;
        std::string nameInput = "";
        playerNamePrompt(&nameInput, &players);
        players.push_back(new Player(nameInput));
        playerNum++;
    }

    // If game mode is single, add computer to players.
    if (mode == single) {
        players.push_back(new Player("COMPUTER"));
    }
    
    // Create a new game of Qwirkle.
    this->game = new Game(this->testFlag, this->enhancedFlag);
    bool gameCreated = false;

    try {
        this->game->newGame(players, mode);
        gameCreated = true;

    // Exit game safely if program error occurs while making game.  
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
        std::cout << std::endl;
        for (Player* player : players) {
            delete player;
            player = nullptr;
        }
        delete this->game;
        this->game = nullptr;
        exitGame();
    }
    
    // If new game is successful, proceed with gameplay.
    if (gameCreated && !this->exitMode) {
        std::cout << "Let's play!" << std::endl;
        std::cout << std::endl;
        baseGameplay();
    }
}

void Controller::playerNamePrompt(std::string* nameInput, 
    const std::vector<Player*>* players) {
    
    bool awaitingInput = true;
    while (awaitingInput) {

        // Get player name input.
        inputPrompt(nameInput);

        // If the player asked for help.
        if (this->enhancedFlag && *nameInput == "Help!") {
            std::cout << "Enter the name of the player "
                         "or enter ^D to quit." << std::endl;
            std::cout << "Names must be unique and can only have capital "
                         "letters (no numbers/symbols)." << std::endl;
            std::cout << "The name COMPUTER is reserved." << std::endl;
            std::cout << std::endl;

        // Check player name is valid. 
        } else {
            bool nameValid = validator->isNameValid(*nameInput, players, 
                this->enhancedFlag);
            if (!nameValid && !std::cin.eof()) {
                std::cout << "Invalid input!" << std::endl;
                std::cout << std::endl;
            } else if (std::cin.eof()) {
                awaitingInput = false;
                exitGame();
            } else {
                awaitingInput = false;
            }
        }
    }
}

void Controller::inputPrompt(std::string* input) {
    std::cout << "> ", getline(std::cin, *input);
    std::cout << std::endl;
}

void Controller::loadGame() {
    std::cout << "Load game" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << std::endl;

    // The program should ask the user for a file.
    std::cout << "Enter the filename from which load a game" << std::endl;

    // User enters the relative path to the saved game file.
    std::string fileName = "";
    inputPrompt(&fileName);

    // If the user asked for help. 
    if (this->enhancedFlag && fileName == "Help!") {
        this->testFlag 
            ? std::cout << "Directory is set to m3-tests." << std::endl
            : std::cout << "Directory is set to savedGames." << std::endl;
        std::cout << "Enter relative path to the saved game file." << std::endl;
        std::cout << "Saved game files must be in .save format." << std::endl;
        std::cout << "Do not enter the .save extension name." << std::endl;
        std::cout << "Filenames can't have whitespace "
                     "or special characters." << std::endl;
        std::cout << std::endl;

    // Load the file.
    } else {
        bool gameLoaded = false;
        try {
            this->game = this->fileHandler->loadGame(fileName);
            gameLoaded = true;

        // If file invalid, show error and go back to main menu. 
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            std::cout << std::endl;
        }

        // If file valid, show success message and continue gameplay. 
        if (gameLoaded) {
            std::cout << "Qwirkle game successfully loaded" << std::endl;
            std::cout << std::endl;
            baseGameplay();
        }
    }
}

void Controller::credits() {
    std::cout << "Credits" << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Carelle Mulawa-Richards" << std::endl;
    std::cout << "Student ID: s3749114" << std::endl;
    std::cout << "Email: s3749114@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Jacob Depares" << std::endl;
    std::cout << "Student ID: s3851480" << std::endl;
    std::cout << "Email: s3851480@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Alexander Barron" << std::endl;
    std::cout << "Student ID: s3831619" << std::endl;
    std::cout << "Email: s3831619@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Arian Najafi Yamchelo" << std::endl;
    std::cout << "Student ID: s3910902" << std::endl;
    std::cout << "Email: s3910902@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;
}

void Controller::exitGame() {
    this->exitMode = true;
    std::cout << std::endl;
    std::cout << "Goodbye" << std::endl;
    std::cout << std::endl;
}

void Controller::baseGameplay() {
    bool gameComplete = this->game->isComplete();
    while (!gameComplete && !this->isExitMode()) {
        takeTurn();
        gameComplete = this->game->isComplete();
    }
    if (!this->isExitMode()) {
        endGame();
    }      
}

void Controller::takeTurn() {

    // The name of the current player.
    std::cout << this->game->getCurrPlayer()->getName()
              << ", it's your turn" << std::endl;
    std::cout << std::endl;

    // The scores of both players.
    playerScores();
    std::cout << std::endl;

    // The state of the board.
    this->game->getBoard()->printBoard();
    std::cout << std::endl;

    // Take turn if player is computer. 
    if (this->game->getCurrPlayer()->getName() == "COMPUTER") {
        std::cout << "COMPUTER is taking its turn..." << std::endl;
        std::cout << std::endl;
        try { 
            this->game->takeTurnForPlayer();

        // If there is a program error and computer can't take turn.
        } catch (std::exception& e) {
            std::cout << "Program error - " << e.what() << std::endl;
            exitGame();
        }

    // Take turn if player is computer human.
    } else {

        // The tiles in the current player’s hand.
        std::cout << "Your hand is" << std::endl;
        this->game->getCurrPlayer()->getHand()->printHand();
        std::cout << std::endl;

        // The user prompt.
        if (!this->exitMode) {
            turnPrompt();
        }
    }
}

void Controller::playerScores() {
    for (Player* player : this->game->getPlayers()) {
        std::cout << "Score for " << player->getName() << ": "
                  << player->getScore() << std::endl;
    }
}

void Controller::turnPrompt() {
    bool awaitingInput = true;
    while (awaitingInput && !isExitMode()) {
        
        // Ask user to enter command.
        std::string commandInput = "";
        inputPrompt(&commandInput);

        // If the player asked for help.
        if (this->enhancedFlag && commandInput == "Help!") {
            std::cout << "Enter one of the follow commands to "
                         "take your turn or enter ^D to quit." << std::endl;
            std::cout << std::endl;
            std::cout << "place <colour><shape> at <row><col>" << std::endl;
            std::cout << "replace <colour><shape>" << std::endl;
            std::cout << "save <filename>" << std::endl;
            std::cout << "skip (only vaild when tile bag empty)" << std::endl;
            std::cout << std::endl;

        // Validate and process command.
        } else {
            int command = validator->isCommandValid(commandInput);

            // If command is invalid.
            if (command == -1) {
                std::cout << "Invalid input!" << std::endl;
                std::cout << std::endl;

            // If command is place <colour><shape> at <row><col>.
            } else if (command == 1) {
                placeTile(commandInput, &awaitingInput);

            // If command is replace <colour><shape>.
            } else if (command == 2) {
                replaceTile(commandInput, &awaitingInput);

            // If command is save <filename>.
            } else if (command == 3) {
                saveGame(commandInput);

            // If command is EOF character ^D.
            } else if (command == 4) {
                awaitingInput = false;
                exitGame();

            // If command is skip.
            } else if (command == 5) {
                skipTurn(&awaitingInput);
            }
        }
    }
}

void Controller::placeTile(std::string commandInput, bool* inputStatus) {

    // Extract tile from input.
    Colour colourInput = commandInput[6];
    Shape shapeInput = commandInput[7] - '0';
    Tile *tileInput = new Tile(colourInput, shapeInput);

    // Extract position from input.
    char rowInput = commandInput[12];
    int colInput;

    if (commandInput.length() > 14) {
        colInput = std::stoi(std::to_string(commandInput[13] - '0') + 
                   std::to_string(commandInput[14] - '0'));
    } else {
        colInput = commandInput[13] - '0';
    }

    try {
        // Place the tile. 
        bool tilePlaced = this->game->placeTile(tileInput, rowInput, colInput);

        // If the tile placement is illegal. 
        if (!tilePlaced) {
            std::cout << "Illegal move!" << std::endl;
            std::cout << std::endl;
            delete tileInput; 
            tileInput = nullptr; 
        } else {
            *inputStatus = false;
        }

    // If there is a program error and the tile can't be placed. 
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
        delete tileInput; 
        tileInput = nullptr;
        exitGame();
    }
}

void Controller::replaceTile(std::string commandInput, bool* inputStatus) {

    // Extract tile from input.
    Colour colourInput = commandInput[8];
    Shape shapeInput = commandInput[9] - '0';
    Tile *tileInput = new Tile(colourInput, shapeInput);

    // Try to replace the tile.
    bool tileReplaced = this->game->replaceTile(tileInput);

    // If replace is illegal. 
    if (!tileReplaced) {
        std::cout << "Illegal move!" << std::endl;
        std::cout << std::endl;
        delete tileInput;
        tileInput = nullptr;

        // Check if skip vailable if tile can't be replaced.
        bool skipAvailable = this->game->isSkipAvailable();

        if (skipAvailable) {
            std::cout << "Tile bag empty - Replace not available, "
                      << "enter 'skip' to go to next player" << std::endl;
            std::cout << std::endl;
        } 
    } else {
        *inputStatus = false;
    }
}

void Controller::skipTurn(bool* inputStatus) {
    bool skipAvailable = skipAvailable = this->game->isSkipAvailable();
    if(skipAvailable) {
        this->game->skipTurn();
    }
    else {
        std::cout << "You can't skip at this stage of the game!" << std::endl;
    }
    *inputStatus = false;
}

void Controller::saveGame(std::string comandInput) {
    
    // Extract file name from input.
    std::string fileNameInput = comandInput.substr(5, comandInput.length());

    // Save the current game to the provided filename.
    try {
        this->fileHandler->saveGame(this->game, fileNameInput);
        std::cout << "Game successfully saved" << std::endl;

    // If the file doesn't pass the validation checks.
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Controller::endGame() {
    std::cout << "Game over" << std::endl;
    std::cout << std::endl;

    // Show scores and name of the winner(s)
    playerScores();
    std::cout << std::endl;
    winners();

    // Quit safely.
    exitGame();
}

void Controller::winners() const {
    std::vector<std::string> winners = this->game->getWinners();
    std::cout << (winners.size() > 1 ? "Players " : "Player "); 
    for (std::string winner : winners) {
        if (winner == winners.back() && winner != winners.front()) {
            std::cout << " and ";
        } else if (winner != winners.front()) {
            std::cout << ", ";
        }
        std::cout << winner;
    }
    std::cout << " won!" << std::endl;
}

bool Controller::isExitMode() const {
    return this->exitMode;
}