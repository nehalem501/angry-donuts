/* index.cpp */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>
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

Entry* Index::get_entry(uuid_t id) {
    for (Entry* e : m_index) {
        if (uuid_compare(id, e->id) == 0)
            return e;
    }
    
    return NULL;
}

void Index::add_entry(Entry *e) {
    m_index.push_front(e);
}

void Index::add(uuid_t id) {

}

bool Index::exists(uuid_t id) {
    return false;
}

Status Index::put(uuid_t id, Data *data) {
    Status status;
    Object object(id, path, data, &status);
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

