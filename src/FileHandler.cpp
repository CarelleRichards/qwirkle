#include "../include/FileHandler.h"

FileHandler::FileHandler(bool testFlag, bool enhancedFlag) {
    this->testFlag = testFlag;
    this->enhancedFlag = enhancedFlag;
}

FileHandler::FileHandler(const FileHandler& other) {
    this->testFlag = other.testFlag;
}

FileHandler::FileHandler(FileHandler&& other) {
    this->testFlag = other.testFlag;
    other.testFlag = false;
}

FileHandler::~FileHandler() {}

void FileHandler::saveGame(const Game* game, const std::string fileNameInput) {

    // Open file and export the game to it.
    std::string path = makeFilePath(fileNameInput);
    std::fstream outFile;
    outFile.open(path, std::ios::out);

    if (outFile.is_open()) {

        // Indicate if game is enhanced and output game mode. 
        if (this->enhancedFlag) {
            outFile << "#enhanced" << std::endl;
            outFile << game->getMode() << std::endl;
        }

        // Output player details. 
        for (Player* player : game->getPlayers()) {
            outFile << player->getName() << std::endl;
            outFile << player->getScore() << std::endl;
            outFile << player->getHand()->getAsStr() << std::endl;
        }

        // Output board width and height.
        int boardHeight = game->getBoard()->getMaxRow() + 1;
        int boardWidth = game->getBoard()->getMaxCol() + 1;
        outFile << boardWidth << "," << boardHeight << std::endl;

        // Output board, tile bag and current player. 
        outFile << game->getBoard()->getAsStr() << std::endl;
        outFile << game->getTileBag()->getAsStr() << std::endl;
        outFile << game->getCurrPlayer()->getName();

        outFile.close();
    }

    // Show error if save file wasn't created. 
    if (!fileExists(fileNameInput)) {
        throw std::invalid_argument("Game did not save correctly!");
    }
}

Game* FileHandler::loadGame(const std::string fileNameInput) {

    // Show error if provided file doesn't exist.
    if (!fileExists(fileNameInput)) {
        throw std::out_of_range("File does not exist!");
    }

    // Open the file and save the contents to a vector.
    std::string path = makeFilePath(fileNameInput);
    std::fstream inFile;
    inFile.open(path);

    std::vector<std::string> fileVec;
    if (inFile.is_open()) {
        std::string line;
        while (getline(inFile, line)) {
            fileVec.push_back(line);
        }
        inFile.close();
    }
    Game* game = gameFromVec(fileVec);

    // Load data from vector and return game if successful. 
    return game;
}

Mode FileHandler::modeFromStr(const std::string modeInput) {
    Mode mode = dual;
    if (modeInput == "1") {
        mode = single;
    } else if (modeInput == "3") {
        mode = triple;
    } else if (modeInput == "4") {
        mode = quad;
    }
    return mode;
}

Game* FileHandler::gameFromVec(const std::vector<std::string> fileVec) {

    // Line in file or pos in vector.
    int line = 0;

    // If enhancements are off, game mode is dual. 
    bool enhancedFlag = false;
    Mode mode = dual; 

    // If enhancements are on, extract game mode.
    if (fileVec[line] == "#enhanced") {
        enhancedFlag = true;
        line++;
        mode = modeFromStr(fileVec[line]);
        line++;
    }

    int totalPlayers = 0;
    if (mode == single || mode == dual) {
        totalPlayers = 2;
    } else if (mode == triple) {
        totalPlayers = 3;
    } else if (mode == quad) {
        totalPlayers = 4;
    }

    // Make players vector from file vector.
    std::vector<Player*> players;
    for (int i = 0; i < totalPlayers; i++) {
        std::string nameStr = fileVec[line];
        line++;
        std::string scoreStr = fileVec[line];
        line++;
        std::string handStr = fileVec[line];
        line++;
        players.push_back(playerFromStr(nameStr, scoreStr, handStr));
    }

    // Extra line with board width and height.
    line++;

    // Make board and tile bag and current player from file vector.
    Board* board = boardFromStr(fileVec[line]);
    line++;
    TileBag* tileBag = tileBagFromStr(fileVec[line]);
    line++;
    int currPlayer = currPlayerFromStr(players, fileVec[line]);
    line++;

    // Load all data into game.
    Game* game = new Game(this->testFlag, enhancedFlag);
    bool loaded = game->loadGame(players, board, tileBag, currPlayer, mode);

    // If unsuccessful, cleanup and show error.
    if (!loaded) {
        for (Player* player : players) {
            delete player;
            player = nullptr;
        }
        players.clear();
        delete board;
        board = nullptr;
        delete tileBag;
        tileBag = nullptr;
        delete game;
        game = nullptr;
        throw std::logic_error("File has incorrect tiles!");
    
    // If successful, cleanup pointers and return game.
    } else {
        board = nullptr;
        tileBag = nullptr;
    }
    return game;
}

Player* FileHandler::playerFromStr(const std::string nameStr, 
    const std::string scoreStr, const std::string handStr) {

    Hand* hand = handFromStr(handStr);
    int score = std::stoi(scoreStr);
    Player* player = new Player(nameStr, score, hand);
    hand = nullptr;
    return player; 
}

Hand* FileHandler::handFromStr(const std::string handStr) {

    Hand* hand = new Hand();

    // Check if the line is empty.
    if (handStr != "") {
        std::stringstream s_stream(handStr);
 
        while (s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ',');

            // Extract tile.
            std::string shapeStr(1, substr[1]);
            Shape shape = std::stoi(shapeStr);
            Colour colour = substr[0];

            // Add to hand.
            hand->addTile(new Tile(colour, shape));
        }
    }
    return hand;
}

Board* FileHandler::boardFromStr(const std::string boardStr) {
    
    Board* board = new Board();

    // Check if the line is empty.
    if (boardStr != "") {
        std::stringstream s_stream(boardStr);

        while (s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ',');
            substr = trim(substr);

            // Extract tile.
            std::string shapeStr(1, substr[1]);
            Shape shape = std::stoi(shapeStr);
            Colour colour = substr[0];

            // Extract position.
            char row = substr[3];
            int col = stoi(substr.substr(substr.find('@') + 2, substr.length()));

            // Add tile to board at position.
            board->addTileAtPos(new Tile(colour, shape), row, col);
        }
    }
    return board;
}

TileBag* FileHandler::tileBagFromStr(const std::string tileBagStr) {
    
    TileBag* tileBag = new TileBag();

    // Check if the line is empty.
    if (tileBagStr != "") {
        std::stringstream s_stream(tileBagStr);

        while (s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ',');

            // Extract tile.
            std::string shapeStr(1, substr[1]);
            Shape shape = std::stoi(shapeStr);
            Colour colour = substr[0];

            // Add tile to tile bag.
            tileBag->addTile(new Tile(colour, shape));
        }
    }
    return tileBag;
}

int FileHandler::currPlayerFromStr(const std::vector<Player*> players,
    const std::string nameStr) const {

    int currPlayer = 0;
    bool found = false;
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->getName() == nameStr && !found) {
            currPlayer = i;
            found = true;
        }
    }
    return currPlayer;
}

std::string FileHandler::trim(const std::string& source) {
    std::string s(source);
    s.erase(0, s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
    return s;
}

bool FileHandler::fileExists(const std::string fileNameInput) {

    // Try to open the file.
    std::string path = makeFilePath(fileNameInput);
    std::fstream infile;
    infile.open(path);

    // If is open, the file exists.
    bool validPath = true;
    if (!infile.is_open()) {
        validPath = false;
    }
    infile.close();

    return validPath;
}

std::string FileHandler::makeFilePath(const std::string fileNameInput) {
    std::string path = "";
    if (this->testFlag && this->enhancedFlag) {
        path += "m3-tests/";
    } else if (this->testFlag) {
        path += "tests/";
    } else {
        path += "savedGames/";
    }
    path += fileNameInput + ".save";
    return path;
}