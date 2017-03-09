/* utils.h */

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <uuid/uuid.h>

std::string get_path(uuid_t id, std::string directory);
std::string get_path2(uuid_t id, std::string directory);
void create_path(std::string root_path, std::string object_path);

#endif // UTILS_H
