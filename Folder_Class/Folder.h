//
// Created by Frank Yang on 5/4/24.
//

#ifndef FOLDER_H
#define FOLDER_H

#include <iostream>
#include <string>
#include "../File_Class/File.h"

class Folder {
    std::string name;
    std::vector <Folder> folder_list;
    std::vector <File> file_list;
public:
    explicit Folder(std::string folder_name): name(std::move(folder_name)) { }
    std::string get_name();

    std::vector<Folder>& get_folder_list();
    std::vector<File>& get_file_list();

    size_t get_count();

    [[nodiscard]] std::vector <std::string> get_content_preview() const;

    File& add_file(const std::string& file_name);
    Folder& add_folder(const std::string& folder_name);

    int rename(const std::string& new_name);
};

#endif //FOLDER_H
