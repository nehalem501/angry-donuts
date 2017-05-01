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
    void set_index_data(std::string path, Data *data);
    Data* get_index_data(std::string path);
    void set(uint8_t *array, unsigned int length, unsigned int position, bool value);
    bool get(uint8_t *array, unsigned int length, unsigned int position);
}

#endif // UTILS_H
