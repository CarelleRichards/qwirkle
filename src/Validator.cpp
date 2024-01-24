#include "../include/Validator.h"

Validator::Validator() {}

Validator::Validator(const Validator &other) {}

Validator::Validator(Validator&& other) {}

Validator::~Validator() {}

bool Validator::isNameValid(const std::string &nameInput,
    const std::vector<Player*>* players, bool enhancedFlag) {

    std::regex nameReg("[A-Z]+");
    std::regex computerReg("COMPUTER");

    // The name COMPUTER is reserved in enhanced mode. 
    bool condition = false;
    if (enhancedFlag) {
        condition = std::regex_match(nameInput, nameReg) &&
            !std::regex_match(nameInput, computerReg);
    } else {
        condition = std::regex_match(nameInput, nameReg);
    }
    
    // Check if name input matches regex and name is unique.
    bool nameValid = false;
    if (condition) {
        nameValid = true;
        for (Player* player : *players) {
            if (nameInput == player->getName()) {
                nameValid = false;
            }
        }
    }
    return nameValid;
}

int Validator::isCommandValid(const std::string &commandInput) {
    int command = -1;

    // Regex for <colour><shape> at <row><col>.
    std::regex placeReg("place [R|O|Y|G|B|P][1-6] at "
                        "[A-Z](0?[0-9]|1[0-9]|2[0-5])\\b");

    // Regex for replace <colour><shape>.
    std::regex replaceReg("replace [R|O|Y|G|B|P][1-6]");

    // Regex or save <filename>. 
    // Name can't have special chars or whitespace.
    std::regex saveReg("save [A-Za-z1-9]+");
    
    // Regex for skip.
    std::regex skipReg("skip");
    
    // Check if regex matches command or if EOF.
    if (std::regex_match(commandInput, placeReg)) {
        command = 1;
    } else if (std::regex_match(commandInput, replaceReg)) {
        command = 2;
    } else if (std::regex_match(commandInput, saveReg)) {
        command = 3;
    } else if (std::cin.eof()) {
        command = 4;
    } else if (std::regex_match(commandInput, skipReg)) {
        command = 5;
    }

    // Return matching command int or -1 if invalid.
    return command;
}