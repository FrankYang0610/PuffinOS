//
// Created by Frank Yang on 4/24/24.
//

#include "File.h"
#include <utility>

int File::rename(std::string new_name) {
    this->name = std::move(new_name);
    return 0;
}
