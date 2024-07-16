//
// Created by Frank Yang on 4/24/24.
//

// THIS IS THE MAIN TERMINAL

#include "../PuffinOS_Class/PuffinOS.h"
#include "Error_Stream/Error_Stream.h"
#include "../Command_Separator/Command_Separator.h"
#include "../Network/Network.h"

void print_process_list(const std::vector <Process> &_processes) {
    for (const auto& process : _processes) {
        std::cout << process.get_id() << ": " << process.get_name() << ", " << "SIZE USAGE = " << process.get_cache_size() << std::endl;
    }
    std::cout << "== END OF PROCESS LIST ==" << std::endl;
}

void print_file_list(const std::vector <File> &_files) {
    for (const auto& file : _files) {
        std::cout << file.get_name() << std::endl;
    }
    std::cout << "== END OF FILE LIST ==" << std::endl;
}

void PuffinOS_Prototype::terminal() {
    std::string command_raw;
    while (std::getline(std::cin, command_raw)) {
        std::vector <std::string> command = separate_command(command_raw);

        if (command.empty()) {
            print_error("EMPTY_COMMAND");
            continue;
        }

        std::string main_operation = command[0];

        if (main_operation == "QUIT") {
            std::cout << "Hasta La Vista!" << std::endl;
            return;
        }

        if (main_operation == "PRINT") {
            if (command.size() != 2) {
                print_error("COMMAND_SYNTAX_ERROR");
            }

            std::string content_to_print = command[1];

            if (content_to_print == "process_list") {
                std::vector <Process> processes = this->get_process_list();
                if (processes.empty()) {
                    std::cout << "== EMPTY PROCESS LIST ==" << std::endl;
                    continue;
                }
                print_process_list(this->get_process_list());
            }

            else if (content_to_print == "root") {
                auto root_content_list_preview = this->get_root_folder().get_content_preview();
                for (const auto& root_content : root_content_list_preview) {
                    std::cout << root_content << std::endl;
                }
            }
            else { // not root folder
                try {
                    const std::string& folder_path = content_to_print;

                    auto parent_of_target_folder = this->get_base_directory(folder_path);

                    bool folder_found = false;

                    for (auto it : parent_of_target_folder.get_folder_list()) {
                        if (it.get_name() == PuffinOS_Prototype::get_directory_components(folder_path).back()) {
                            auto content_list_preview = it.get_content_preview();
                            for (const auto& content : content_list_preview) {
                                std::cout << content << std::endl;
                            }
                            folder_found = true;
                            break;
                        }
                    }

                    if (!folder_found) {
                        throw std::runtime_error("FOLDER_NOT_EXIST");
                    }
                } catch (const std::exception &e) {
                    print_error(e.what());
                    std::cout << "== PRINT FOLDER FAILED ==" << std::endl;
                }
            }

            continue;
        }

        if (main_operation == "NEW" || main_operation == "ADD" || main_operation == "CREATE") {
            if (command.size() < 3) {
                print_error("COMMAND_SYNTAX_ERROR");
                continue;
            }

            std::string type_name = command[1];
            std::string rep_policy = (command.size() == 4) ? command[3] : "N_REP";

            if (type_name == "FOLDER") {
                std::string folder_path = command[2];

                if (folder_path[0] != '/') {
                    folder_path.insert(0, "/");
                }
                try {
                    this->add_folder(folder_path, rep_policy == "REP");
                    std::cout << "== CREATE FOLDER SUCCESS: " << folder_path << " " << "==" << std::endl;
                } catch (const std::exception &e) {
                    print_error(e.what());
                    std::cout << "== CREATE FOLDER FAILED: " << folder_path << " " << "==" << std::endl;
                }
                continue;
            }

            if (type_name == "FILE") {
                std::string file_path = command[2];

                if (rep_policy != "REP" && rep_policy != "N_REP") {
                    print_error("COMMAND_SYNTAX_ERROR");
                    continue;
                }

                if (file_path[0] != '/') {
                    file_path.insert(0, "/");
                }

                try {
                    this->add_file(file_path, rep_policy == "REP");
                    std::cout << "== CREATE FILE SUCCESS: " << file_path << " " << "==" << std::endl;
                } catch (const std::exception &e) {
                    print_error(e.what());
                    std::cout << "== CREATE FILE FAILED: " << file_path << " " << "==" << std::endl;
                }

                continue;
            }

            if (type_name == "PROCESS" && command.size() == 3) {
                print_error("UNAVAILABLE_FEATURE");
                continue;
            }

            print_error("COMMAND_SYNTAX_ERROR");
        }

        if (main_operation == "RENAME") {
            if (command.size() != 3) {
                print_error("COMMAND_SYNTAX_ERROR");
                continue;
            }

            std::string file_path = command[1];
            std::string new_filename = command[2];

            try {
                this->rename_file(file_path, new_filename);
            std::cout << "== RENAME FILE SUCCESS: " << PuffinOS_Prototype::get_directory_components(file_path).back() << " → " << new_filename << " " << "==" <<std::endl;
            } catch (const std::exception &e) {
                print_error(e.what());
                std::cout << "== RENAME FILE FAILED: " << PuffinOS_Prototype::get_directory_components(file_path).back() << " → " << new_filename << " " << "==" <<std::endl;
            }

            continue;
        }

        if (main_operation == "DELETE") {
            if (command.size() < 2) {
                print_error("COMMAND_SYNTAX_ERROR");
                continue;
            }

            std::string type_name = (command.size() == 3) ? command[1] : "FILE";

            if (type_name == "FOLDER") {
                std::string folder_path = command[2];

                if (folder_path[0] != '/') {
                    folder_path.insert(0, "/");
                }

                try {
                    this->delete_folder(folder_path);
                    std::cout << "== DELETE FOLDER SUCCESS: " << folder_path << " " << "==" << std::endl;
                } catch (const std::exception &e) {
                    print_error(e.what());
                    std::cout << "== DELETE FOLDER FAILED: " << folder_path << " " << "==" << std::endl;
                }

                continue;
            }

            if (type_name == "FILE") {
                std::string file_name = command[command.size() - 1];

                if (file_name[0] != '/') {
                    file_name.insert(0, "/");
                }

                try {
                    this->delete_file(file_name);
                    std::cout << "== DELETE FILE SUCCESS: " << file_name << " " << "==" << std::endl;
                } catch (const std::exception &e) {
                    print_error(e.what());
                    std::cout << "== DELETE FILE FAILED: " << file_name << " " << "==" << std::endl;
                }
                continue;
            }
        }

        if (main_operation == "TEST") {
            if (command.size() < 2) {
                print_error("COMMAND_SYNTAX_ERROR");
                continue;
            }

            std::string content = command[1];

            if (content == "connection" || content == "networl") {
                if (is_network_available()) {
                    std::cout << "NETWORK CONNECTION IS AVAILABLE" << std::endl;
                } else {
                    std::cout << "NETWORK CONNECTION IS [NOT] AVAILABLE" << std::endl;
                }
            }
            continue;
        }

        print_error("COMMAND_NOT_FOUND");
    }
}
