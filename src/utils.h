/* utils.h */

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <uuid/uuid.h>

std::string get_path(uuid_t id, std::string directory);

#endif // UTILS_H
