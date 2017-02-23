/* utils.cpp */

#include <string>
#include <uuid/uuid.h>

#include "utils.h"

using namespace std;

string get_path(uuid_t id, string directory) {
    char path_str[37];
    uuid_unparse(id, path_str);
    string path(path_str);
    directory.append(path);
    return directory;
}
