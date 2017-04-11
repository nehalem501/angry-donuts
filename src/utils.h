/* utils.h */

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <string>
#include <uuid/uuid.h>

#define INDEX_SIZE_BITS 256
#define INDEX_SIZE_BYTES INDEX_SIZE_BITS / 8

std::string get_path(uuid_t id, std::string directory);
std::string get_path2(uuid_t id, std::string directory);
void create_path(std::string root_path, std::string object_path);
void set(uint8_t *array, unsigned int length, unsigned int position, bool value);
bool get(uint8_t *array, unsigned int length, unsigned int position);

#endif // UTILS_H
