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

Entry::Entry(uuid_t uuid, Object *obj) : object(obj), nb_opened(0), del(false) {
    uuid_copy(id, uuid);
}

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
    Entry *entry = get_entry(id);
    if (entry != NULL) {
        entry->object->put(id, data, &status);
    } else {
        Object *object = new Object(id, path, data, &status);
        if (status == Status::Success) {
            Entry *entry = new Entry(id, object);
            add_entry(entry);
        } else {
            if (object == NULL)
                status = Status::Error;
        }
    }
    return status;
}

Status Index::get(uuid_t id, Data *data) {
    Status status = Status::Success;
    Entry *entry = get_entry(id);
    if (entry != NULL) {
        entry->object->get(data);
    } else {
        Object *object = new Object(id, path, &status);
        if (status == Status::Success) {
            Entry *entry = new Entry(id, object);
            add_entry(entry);
            object->get(data);
        } else {
            if (object == NULL)
                status = Status::Error;
        }
    }
    return status;
}

Status Index::del(uuid_t id) {
    Entry *entry = get_entry(id);
    if (entry != NULL) {
        entry->del = true;
    } else {
        std::string obj_path = get_path(id, path);
        if (unlink(obj_path.c_str()) == 0) {
            return Status::Success;
        } else {
            perror("unlink");
            return Status::Error;
        }
    }
    return Status::Success;
}

int64_t Index::get_size(uuid_t id) {
    Status status;
    Object object(id, path, &status);

    if (status == Status::Success)
        return (int64_t) object.get_size();

    return -1;
}

void Index::open(uuid_t id) {
    Status status = Status::Success;
    Entry *entry = get_entry(id);
    if (entry != NULL) {
        entry->nb_opened++;
    } else {
        Object *object = new Object(id, path, &status);
        if (status == Status::Success) {
            Entry *entry = new Entry(id, object);
            add_entry(entry);
            entry->nb_opened++;
        } else {
            delete object;
        }
    }
}

void Index::close(uuid_t id) {
    Entry *entry = get_entry(id);
    if (entry != NULL) {
        if (entry->nb_opened == 0 || entry->nb_opened == 1) {
            m_index.remove(entry);
            if (entry->del)
                del(id);
            delete entry->object;
            delete entry;
        } else {
            entry->nb_opened--;
        }
    }
}
