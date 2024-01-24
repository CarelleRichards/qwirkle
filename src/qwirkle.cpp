#include "../include/Controller.h"
#include "../include/Player.h"
#include <iostream>
#include <typeinfo>

int main(int argc, char* argv[]) {

    // When test flag is true, a random seed is set 
    // to ensure consistent randomness of the tile bag.
    // Run with "-T" to activate test mode. 
    bool testFlag = false;

    // When enhanced flag is true, enhanced capabilities will 
    // be enabled. Run with "-E" to activate enhanced mode.
    // (1) 3-4 players.
    // (2) Player vs. robot.
    // (3) Help! command.
    bool enhancedFlag = false;

    for (int i = 0; i < argc; i++) {
        std::string argvStr(argv[i]);
        if (argvStr == "-T") {
            testFlag = true;
        } else if (argvStr == "-E") {
            enhancedFlag = true;
        }
    }

    // Run Qwirkle program.
    Controller* controller = new Controller(testFlag, enhancedFlag);
    controller->launchGame();

    delete controller;
    controller = nullptr;

    return EXIT_SUCCESS;
}