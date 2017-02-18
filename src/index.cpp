/* index.cpp */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <uuid/uuid.h>

#include "status.h"
#include "object.h"
#include "index.h"

Index::Index(char *pathname) {
    // Check if given path is a directory
    struct stat s;
    if (!(stat(pathname, &s) == 0 && S_ISDIR(s.st_mode))) {
        std::cout << "Error: " << pathname << " is not a directory" << std::endl;
        exit(EXIT_FAILURE);
    }

    path.insert(0, pathname);
    if (path.back() != '/')
        path.append("/");
}

Status Index::put(uuid_t returned_id, Data *data) {
    Status status;
    Object object(returned_id, path, data, &status, true);
    return status;
}

Status Index::get(uuid_t id, Data *data) {
    Status status;
    Object object(id, path, &status);
    if (status == Status::Success) {
        object.get(data);
    }
    return status;
}

Status Index::del(uuid_t id) {
    return Status::Success;
}

