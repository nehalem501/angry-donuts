/* index.cpp */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <uuid/uuid.h>

#include "status.h"
#include "utils.h"
#include "object.h"
#include "index.h"

using namespace AngryB;

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

Index::Index(std::string pathname) {
    // Check if given path is a directory
    struct stat s;
    if (!(stat(pathname.c_str(), &s) == 0 && S_ISDIR(s.st_mode))) {
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
    std::string obj_path = get_path(id, path);
    if (unlink(obj_path.c_str()) == 0) {
        return Status::Success;
    } else {
        perror("bla bla unlink");
        return Status::Error;
    }
}

int64_t Index::get_size(uuid_t id) {
    Status status;
    Object object(id, path, &status);

    if (status == Status::Success)
        return (int64_t) object.get_size();

    return -1;
}

