//
// Created by Frank Yang on 4/24/24.
//

#include "Command_Separator.h"

std::vector <std::string> separate_command(const std::string &raw_command) {
    std::istringstream iss(raw_command);
    std::vector <std::string> command;
    std::string word;
    while (iss >> word) {
        command.emplace_back(word);
    }
    return command;
}
