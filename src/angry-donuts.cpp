/* main.cpp */

#include <iostream>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Error: missing argument" << std::endl;
        std::cout << "Usage: angry-donuts /path/to/data" << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
