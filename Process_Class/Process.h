//
// Created by Frank Yang on 4/24/24.
//

#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <utility>

#define NORMAL 0
#define ERROR (-1)
#define WAITING 2

class Process {
private:
    size_t id;
    std::string name;
    size_t cache_size;
public:
    Process(size_t id, std::string name, size_t cache_size): id(id), name(std::move(name)), cache_size(cache_size) {}
    [[nodiscard]] size_t get_id() const { return this->id; }
    [[nodiscard]] std::string get_name() const { return this->name; }
    [[nodiscard]] size_t get_cache_size() const { return this->cache_size; }
};

#endif //PROCESS_H
