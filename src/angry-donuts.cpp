/* main.cpp */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <uuid/uuid.h>
#include <string>
#include <string.h>
#include <iostream>

#include "index.h"
#include "status.h"
#include "data.h"

void usage(std::string str) {
    std::cout << "Error: " << str << std::endl;
    std::cout << "Usage: angry-donuts /path/to/data" << std::endl;
}

void check_uuid(const char *str, uuid_t uuid) {
    if (uuid_parse(str, uuid) != 0) {
        std::cout << str << " is not a valid UUID" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void get(Index *index, const char *id, const char *file) {
    uuid_t uuid;
    check_uuid(id, uuid);

    Data data;    
    if (index->get(uuid, &data) != Status::Success) {
        std::cout << "error get" << std::endl;
        // Print error
        exit(EXIT_FAILURE);
    }

    if (file == NULL) {
        // Object content will be written to stdout
        int64_t written = 0;
        int64_t remaining = (int64_t) data.length;
        uint8_t *bytes = data.bytes;
        while (remaining) {
            written = write(STDOUT_FILENO, bytes, remaining);
            if (written < 0) {
                perror("write error");
                exit(EXIT_FAILURE);
            }
            remaining -= written;
            bytes += written;
        }
    } else {
        // Object content will be written to file
        int fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open error");
            exit(EXIT_FAILURE);
        }

        int64_t written = 0;
        int64_t remaining = (int64_t) data.length;
        uint8_t *bytes = data.bytes;
        while (remaining) {
            written = write(fd, bytes, remaining);
            if (written < 0) {
                perror("write error");
                exit(EXIT_FAILURE);
            }
            remaining -= written;
            bytes += written;
        }

        close(fd);
    }
}

void put(Index *index, const char *id, const char *file) {
    uuid_t uuid;
    bool new_obj = false;
    if (id == NULL) {
        uuid_generate(uuid);
        new_obj = true;
    } else {
        check_uuid(id, uuid);
    }

    Data data;

    int fd = open(file, O_RDONLY);
    if (fd == -1) {
        perror("error open");
        exit(EXIT_FAILURE);
    }

    struct stat64 sb;
    if (fstat64(fd, &sb) == -1) {
        perror("error fstat64");
        exit(EXIT_FAILURE);
    }

    data.length = (uint64_t) sb.st_size;
    data.bytes = (uint8_t *) mmap(NULL, data.length, PROT_READ, MAP_SHARED, fd, 0);
    if (data.bytes == MAP_FAILED) {
        close(fd);
        perror("error mmap");
        exit(EXIT_FAILURE);
    }

    if (index->put(uuid, &data) != Status::Success) {
        close(fd);
        std::cout << "error put" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (munmap(data.bytes, data.length) != 0)
        perror("error munmap");

    if (new_obj) {
        char str[37];
        uuid_unparse(uuid, str);
        std::cout << "UUID for new object: " << str << std::endl;
    }

    close(fd);
}

void del(Index *index, const char *id) {
    uuid_t uuid;
    check_uuid(id, uuid);

    if (index->del(uuid) == Status::Success)
        std::cout << id << " successfully deleted!" << std::endl;
    else {
        std::cout << "error deleting " << id << " ..." << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        usage("missing arguments");
        exit(EXIT_FAILURE);
    } else if (argc > 5) {
        usage("too many arguments");
        exit(EXIT_FAILURE);
    }

    // Load index
    Index index(argv[1]);

    if (strcmp(argv[2], "put") == 0) {
        if (argc == 4)
            put(&index, NULL, argv[3]);
        else
            put(&index, argv[3], argv[4]);
    } else if (strcmp(argv[2],"get") == 0) {
        if (argc == 4)
            get(&index, argv[3], NULL);
        else
            get(&index, argv[3], argv[4]);
    } else if (strcmp(argv[2],"del") == 0) {
        if (argc == 4)
            del(&index, argv[3]);
        else {
            usage("too many arguments for del");
            exit(EXIT_FAILURE);
        }
    } else {
        usage("unknown command " + std::string(argv[3]));
        exit(EXIT_FAILURE);
    }
    /*
       std::string t = "Bla bla bla!";
       const char *test = t.c_str();
       uint64_t length = strlen(test);
       Data data((uint8_t*) test, length);

       uuid_t uuid;

       if (index.put(uuid, &data) != Status::Success)
       std::cout << "error put" << std::endl;
       Data data2;

       if (length != data2.length) {
       std::cout << "error, different content (length)" << std::endl;
       } else {
       if (memcmp(data.bytes, data2.bytes, length) != 0)
       std::cout << "error, different content (bytes)" << std::endl;
       else
       std::cout << "success on put and get!" << std::endl;
       }

     */
    return 0;
}
