//
// Created by Frank Yang on 4/24/24.
//

#ifndef FILE_H
#define FILE_H

#include <string>
#include <utility>
#include <vector>
#include "../Time_Stamp/Time_Stamp.h"

class File {
private:
    size_t id;
    std::string name;
    std::vector <std::string> content;
public:
    explicit File(std::string file_name): id(std::stoi(time_stamp())), name(std::move(file_name)), content(NULL) { }

    [[nodiscard]] size_t get_id() const { return this->id; }
    [[nodiscard]] std::string get_name() const { return this->name; }
    [[nodiscard]] std::vector <std::string> get_content() const { return this->content; }
    int rename(std::string new_name); // return 0 if success
};

#endif //FILE_H
