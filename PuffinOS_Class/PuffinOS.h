//
// Created by Frank Yang on 4/24/24.
//

#ifndef PUFFINOS_H
#define PUFFINOS_H

#include <sstream>
#include "../Process_Class/Process.h"
#include "../File_Class/File.h"
#include "../Time_Stamp/Time_Stamp.h"

// SYSTEM STATUS
#define SYSTEM_ON 1
#define SYSTEM_OFF 0

// HARDWARE RELATED SIMULATION
#define MEM_LIMIT 50000

// MEMORY USAGE
#define MIN_MEM_USAGE 0
#define MAX_MEM_USAGE MEM_LIMIT

#include <iostream> // for tests
#include <vector>
#include <queue>
#include "../File_Class/File.h"
#include "../Folder_Class/Folder.h"

inline class PuffinOS_Prototype {
private:
    int status = 0;
    size_t mem_usage = 0;
    std::vector <Process> processes;
    Folder root_folder = Folder("root");
    Folder error_folder = Folder("__err");
public:
    int boot();
    void shut_down();

    [[nodiscard]] size_t get_mem_usage() const { return this->mem_usage; }
    [[nodiscard]] std::vector <Process> get_process_list() const { return this->processes; }
    [[nodiscard]] Folder& get_root_folder() { return this->root_folder; }
    
    // Process
    int add_process(const Process& process); // return 0 if success
    int delete_process(size_t id); // return 0 if success
    int clear_process(); // return 0 if success

    void terminal();

    static std::vector <std::string> get_directory_components(const std::string &file_name);
    Folder& get_base_directory(const std::string &directory);

    // Folders and files
    void add_folder(const std::string &folder_path, bool rep);
    void add_file(const std::string &file_path, bool rep);
    void delete_folder(const std::string &folder_path);
    void delete_file(const std::string &file_path);
    void rename_folder(const std::string &original_folder_directory, const std::string &new_folder_name);
    void rename_file(const std::string &file_path, const std::string &new_file_name);
} PuffinOS;

#endif //PUFFINOS_H
