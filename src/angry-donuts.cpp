/* main.cpp */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <uuid/uuid.h>

#include "index.h"
#include "status.h"
#include "data.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Error: missing argument" << std::endl;
        std::cout << "Usage: angry-donuts /path/to/data" << std::endl;
        exit(EXIT_FAILURE);
    }

    Index index(argv[1]);

    std::string t = "Bla bla bla!";
    const char *test = t.c_str();
    uint64_t length = strlen(test);
    Data data((uint8_t*) test, length);

    uuid_t uuid;
    if (index.put(uuid, &data) != Status::Success)
        std::cout << "error put" << std::endl;

    Data data2;
    if (index.get(uuid, &data2) != Status::Success)
        std::cout << "error get" << std::endl;

    if (length != data2.length) {
        std::cout << "error, different content (length)" << std::endl;
    } else {
        if (memcmp(data.bytes, data2.bytes, length) != 0)
            std::cout << "error, different content (bytes)" << std::endl;
        else
            std::cout << "success on put and get!" << std::endl;
    }

    return 0;
}
