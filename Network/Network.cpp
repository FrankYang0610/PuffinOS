//
// Created by Frank Yang on 5/12/24.
//

#include "Network.h"

bool is_network_available() {
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("ping -c 4 www.google.com", "r"), pclose);
    if (!pipe) {
        return false;
    }

    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }

    return result.find(" 0% packet loss") != std::string::npos;
}
