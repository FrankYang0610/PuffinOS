//
// Created by Frank Yang on 4/24/24.
//

#include "PuffinOS.h"

int PuffinOS_Prototype::boot() {
    this->add_process(Process(0, "KERNEL", 100));
    this->add_process(Process(1,"file_manager",200));
    this->status = SYSTEM_ON;
    return 0;
}

void PuffinOS_Prototype::shut_down() {
    this->clear_process();
    this->status = SYSTEM_OFF;
}

// Process
int PuffinOS_Prototype::add_process(const Process& process) {
    if (get_mem_usage() + process.get_cache_size() > MAX_MEM_USAGE) {
        return -1;
    }
    this->mem_usage += process.get_cache_size();
    this->processes.emplace_back(process);
    return 0;
}

int PuffinOS_Prototype::delete_process(size_t id) {
    for (auto it = this->processes.begin(); it != this->processes.end(); ++it) {
        if (it->get_id() == id) {
            this->mem_usage -= it->get_cache_size();
            this->processes.erase(it);
            return 1;
        }
    }
    return -1;
}

int PuffinOS_Prototype::clear_process() {
    this->processes.clear();
    this->mem_usage = 0;
    return 0;
}

// Find file path components
std::vector <std::string> PuffinOS_Prototype::get_directory_components(const std::string &file_name) {
    std::vector <std::string> directory_components;
    std::string component;
    std::istringstream iss(file_name);

    while (std::getline(iss, component, '/')) {
        if (!component.empty()) {
            directory_components.emplace_back(component);
        }
    }
    return directory_components;
}

// Get folder pointer
Folder& PuffinOS_Prototype::get_base_directory(const std::string &directory) { // returns the base directory folder
    std::vector <std::string> directory_components = get_directory_components(directory);

    Folder* current_directory = &(this->root_folder);

    if (directory_components.size() == 1) {
        return *current_directory;
    }

    for (size_t cursor = 0; cursor < directory_components.size() - 1; cursor++) {
        std::string current_directory_name = directory_components[cursor];

        auto& current_directory_folder_list = current_directory->get_folder_list();

        bool need_to_create_new_folder = true;

        if (!current_directory_folder_list.empty()) {
            for (auto & it : current_directory_folder_list) {
                if (it.get_name() == current_directory_name) {
                    current_directory = &it;
                    need_to_create_new_folder = false;
                    break;
                }
            }
        }

        if (need_to_create_new_folder) {
            current_directory = &(current_directory->add_folder(current_directory_name));
        }
    }
    return *current_directory;
}

void PuffinOS_Prototype::add_folder(const std::string &folder_path, bool rep) {
    auto folder_path_components = get_directory_components(folder_path);
    std::string folder_name = folder_path_components.back();

    Folder& target_directory = get_base_directory(folder_path);

    auto& target_directory_file_list = target_directory.get_folder_list();
    auto conflict_iterator = target_directory_file_list.begin();

    // Now current folder is right.

    for (; conflict_iterator != target_directory_file_list.end(); ++conflict_iterator) {
        if (conflict_iterator->get_name() == folder_name) {
            break;
        }
    }

    if (conflict_iterator == target_directory_file_list.end()) {
        target_directory.add_folder(folder_name);
        return;
    }

    if (rep == true) {
        *conflict_iterator = Folder(folder_name);
        return;
    } else {
        folder_name = time_stamp() + folder_name;
        target_directory.add_folder(folder_name);
        return;
    }
}

// Folders and files
void PuffinOS_Prototype::add_file(const std::string &file_path, bool rep) {
    auto file_path_components = get_directory_components(file_path);
    std::string file_name = file_path_components.back();

    Folder& target_directory = get_base_directory(file_path);

    auto& target_directory_file_list = target_directory.get_file_list();
    auto conflict_iterator = target_directory_file_list.begin();

    // Now current folder is right.

    for (; conflict_iterator != target_directory_file_list.end(); ++conflict_iterator) {
        if (conflict_iterator->get_name() == file_name) {
            break;
        }
    }

    if (conflict_iterator == target_directory_file_list.end()) {
        target_directory.add_file(file_name);
        return;
    }

    if (rep == true) {
        *conflict_iterator = File(file_name);
        return;
    } else {
        file_name = time_stamp() + file_name;
        target_directory.add_file(file_name);
        return;
    }
}

void PuffinOS_Prototype::delete_folder(const std::string &folder_path) {
    auto file_path_components = get_directory_components(folder_path);
    std::string folder_name = file_path_components.back();

    Folder& target_directory = get_base_directory(folder_path);
    auto& target_directory_folder_list = target_directory.get_folder_list(); // This is a reference

    for (auto it = target_directory_folder_list.begin(); it != target_directory_folder_list.end(); ++it) {
        if (it->get_name() == folder_name) {
            target_directory_folder_list.erase(it);
            return;
        }
    }

    throw std::runtime_error("FOLDER_NOT_EXIST");
}

void PuffinOS_Prototype::delete_file(const std::string &file_path) {
    auto file_path_components = get_directory_components(file_path);
    std::string file_name = file_path_components.back();

    Folder& target_directory = get_base_directory(file_path);
    auto& target_directory_file_list = target_directory.get_file_list(); // This is a reference

    for (auto it = target_directory_file_list.begin(); it != target_directory_file_list.end(); ++it) {
        if (it->get_name() == file_name) {
            target_directory_file_list.erase(it);
            return;
        }
    }

    throw std::runtime_error("FILE_NOT_EXIST");
}

void PuffinOS_Prototype::rename_folder(const std::string &original_folder_directory, const std::string &new_folder_name) {
    auto file_path_components = get_directory_components(original_folder_directory);
    std::string original_folder_name = file_path_components.back();

    Folder& target_directory = get_base_directory(original_folder_directory);
    auto& target_directory_folder_list = target_directory.get_folder_list(); // This is a reference

    // No repeats
    for (auto & it : target_directory_folder_list) {
        if (it.get_name() == new_folder_name) {
            throw std::runtime_error("FOLDER_CONFLICT");
        }
    }

    for (auto & it : target_directory_folder_list) {
        if (it.get_name() == original_folder_name) {
            it.rename(original_folder_directory);
            return;
        }
    }

    throw std::runtime_error("FOLDER_NOT_EXIST");
}

void PuffinOS_Prototype::rename_file(const std::string &file_path, const std::string &new_file_name) {
    auto file_path_components = get_directory_components(file_path);
    std::string original_file_name = file_path_components.back();

    Folder& target_directory = get_base_directory(file_path);
    auto& target_directory_file_list = target_directory.get_file_list(); // This is a reference

    for (auto & it : target_directory_file_list) {
        if (it.get_name() == new_file_name) {
            throw std::runtime_error("FILE_CONFLICT");
        }
    }

    for (auto & it : target_directory_file_list) {
        if (it.get_name() == original_file_name) {
            it.rename(new_file_name);
            return;
        }
    }

    throw std::runtime_error("FILE_NOT_EXIST");
}
