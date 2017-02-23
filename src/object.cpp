/* object.cpp */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <uuid/uuid.h>
#include <string>
#include <string.h>
#include <iostream>

#include "utils.h"
#include "status.h"
#include "data.h"
#include "object.h"

using namespace std;

// Opens a file in read-only mode and maps the file's content in memory
Object::Object(uuid_t id, string data_dir, Status *status) {
    path = get_path(id, data_dir);
    open_file_read(status);
}

// Generates a new UUID if creating a new file and write the data to the file
// then opens it read-only mode and maps the file's content in memory
Object::Object(uuid_t id, string data_dir, Data *d, Status *status, bool create) {
    if (create)
        uuid_generate(id);
        
    *status = Status::Error;
    path = get_path(id, data_dir);
    length = d->length;
    
    int fd = open(path.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("bla bla open");
        return;
    }
    
    int64_t written = 0;
    int64_t remaining = (int64_t) length;
    data = d->bytes;
    while (remaining) {
        written = write(fd, data, remaining);
        if (written < 0) {
            perror("write error");
            return;
        }
        remaining -= written;
        data += written;
    }
    
    close(fd);
    
    open_file_read(status);
}

void Object::open_file_read(Status *status) {
    *status = Status::Error;
    
    int fd = open(path.c_str(), O_RDONLY);
    if (fd == -1) {
        perror("bla bla open");
        return;
    }

    struct stat64 sb;
    if (fstat64(fd, &sb) == -1) {
        perror("bla bla fstat64");
        return;
    }

    length = (uint64_t) sb.st_size;
    data = (uint8_t *) mmap(NULL, length, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        perror("bla bla mmap");
        return;
    }
    
    *status = Status::Success;
}

Object::~Object() {
    if (munmap(data, length) != 0)
        perror("bla bla munmap");
}

void Object::get(Data *data) {
    data->bytes = new uint8_t[length];
    data->length = length;
    memcpy(data->bytes, this->data, length);
}
