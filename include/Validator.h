#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include "Player.h"

class Validator {

   public:

    Validator();
    Validator(const Validator &other);
    Validator(Validator &&other);
    ~Validator();

    // Takes a name input string and true if the name is valid.
    // Players should only consist of letters, no numbers or symbols. 
    // The name COMPUTER is reserved in enhanced mode. 
    bool isNameValid(const std::string &input, 
      const std::vector<Player*>* players, bool enhancedFlag);

    // Checks if a command input is valid and returns a number, depending 
    // on what the command is. If invalid command, returns -1.
    int isCommandValid(const std::string &command);

   private:
};

#endif  // VALIDATOR_H