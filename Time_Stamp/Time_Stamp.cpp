//
// Created by Frank Yang on 4/24/24.
//

#include "Time_Stamp.h"

std::string time_stamp() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    std::string time_stamp = std::to_string(ltm->tm_sec);
    return time_stamp;
}
