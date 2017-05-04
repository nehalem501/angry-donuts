/* utils.h */

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <string>
#include <vector>
#include <uuid/uuid.h>

#include "data.h"

#define INDEX_SIZE_BITS 256
#define INDEX_SIZE_BYTES INDEX_SIZE_BITS / 8

namespace AngryB {
    std::string get_path(uuid_t id, std::string directory);
    std::vector<std::string> split(std::string str, char c);
    std::string create_path(std::string root_path, std::vector<std::string> vec);
    std::string get_index_path(uuid_t id, std::string directory);
    unsigned int get_position(uuid_t id);
    void set_index_data(std::string path, Data *data);
    void get_index_data(std::string path, Data *d);
    void set_bit(Data *d, unsigned int position, bool value);
    bool get_bit(Data *d, unsigned int position);
}

#endif // UTILS_H
