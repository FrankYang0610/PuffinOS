//
// Created by Frank Yang on 5/4/24.
//

#include "Folder.h"

std::string Folder::get_name() {
    return this->name;
}

std::vector<Folder> &Folder::get_folder_list() {
    return this->folder_list;
}

std::vector<File> &Folder::get_file_list() {
    return this->file_list;
}

size_t Folder::get_count() {
    return this->folder_list.size() + this->file_list.size();
}

std::vector<std::string> Folder::get_content_preview() const {
    std::vector <std::string> folder_contents_preview;
    if (!this->folder_list.empty()) {
        for (auto it : this->folder_list) {
            folder_contents_preview.emplace_back("[FOLDER] " + it.get_name()); 
        }
    }
    if (!this->file_list.empty()) {
        for (const auto& it : this->file_list) {
            folder_contents_preview.emplace_back(it.get_name());
        }
    }
    if (folder_contents_preview.empty()) {
        folder_contents_preview.emplace_back("== EMPTY FOLDER ==");
    } else {
        folder_contents_preview.emplace_back("== END OF FOLDER ==");
    }
    return folder_contents_preview;
}

File& Folder::add_file(const std::string& file_name) {
    this->file_list.emplace_back(file_name);
    return this->file_list[this->file_list.size() - 1];
}

Folder& Folder::add_folder(const std::string &folder_name) {
    this->folder_list.emplace_back(folder_name);
    return this->folder_list[this->folder_list.size() - 1];
}

int Folder::rename(const std::string &new_name) {
    this->name = new_name;
    return 0;
}
