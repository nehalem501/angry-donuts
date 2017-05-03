/* utils.cpp */

#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <uuid/uuid.h>

#include "data.h"
#include "utils.h"

using namespace std;

namespace AngryB {
    string get_path(uuid_t id, string directory) {
        char path_str[37];
        uuid_unparse(id, path_str);
        string path(path_str);

        vector<string> first_split = split(path, '-');

        vector<string> vec;
        vec.push_back(first_split[0].substr(0, 4));
        vec.push_back(first_split[0].substr(4, 4));
        vec.push_back(first_split[1]);
        vec.push_back(first_split[2]);
        vec.push_back(first_split[3]);
        vec.push_back(first_split[4].substr(0, 4));
        vec.push_back(first_split[4].substr(4, 4));
        vec.push_back(first_split[4].substr(8, 2));

        path = create_path(directory, vec);
        path.append("/");
        path.append(first_split[4].substr(10, 2));

        return path;
    }

    string create_path(string root_path, vector<string> vec) {
        string path = root_path;
        for(string s : vec) {
            path += "/" + s;
            mkdir(path.c_str(), ACCESSPERMS);
        }

        return path;
    }

    uint8_t byte[] = {
    /* 0b00000001 */ 0x01,
    /* 0b00000010 */ 0x02,
    /* 0b00000100 */ 0x04,
    /* 0b00001000 */ 0x08,
    /* 0b00010000 */ 0x10,
    /* 0b00100000 */ 0x20,
    /* 0b01000000 */ 0x40,
    /* 0b10000000 */ 0x80
    };

    void set_index_data(std::string path, Data *data) {
        path.append("/index");

        int fd = open(path.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open");
            return;
        }

        int written = 0;
        int remaining = (int) data->length;
        uint8_t *data_to_write = data->bytes;
        while (remaining) {
            written = write(fd, data_to_write, remaining);
            if (written < 0) {
                perror("write error");
                close(fd);
                return;
            }
            remaining -= written;
            data_to_write += written;
        }

        close(fd);
    }

    void get_index_data(std::string path, Data *d) {
        path.append("/index");

        int fd = open(path.c_str(), O_RDONLY);
        if (fd == -1) {
            perror("open");
            return;
        }

        struct stat sb;
        if (fstat(fd, &sb) == -1) {
            perror("fstat");
            return;
        }

        int length = sb.st_size;
        uint8_t *data = (uint8_t *) mmap(NULL, length, PROT_READ, MAP_SHARED, fd, 0);
        if (data == MAP_FAILED) {
            perror("mmap");
            return;
        }

        d->bytes = new uint8_t[length];
        d->length = length;
        memcpy(d->bytes, data, length);

        if (munmap(data, length) != 0)
            perror("munmap");
    }

    void set(Data *d, unsigned int position, bool value) {
        if (position >= d->length * 8) {
            std::cout << "error: set: position greater than length of array" << std::endl;
            return;
        }

        unsigned int pos_bytes = position / 8;
        unsigned int pos_bits = position % 8;

        if (value) {
            d->bytes[pos_bytes] = d->bytes[pos_bytes] | byte[pos_bits];
        } else {
            d->bytes[pos_bytes] = d->bytes[pos_bytes] & ~byte[pos_bits];
        }
    }

    bool get(Data *d, unsigned int position) {
        if (position >= d->length * 8) {
            std::cout << "error: get: position greater than length of array" << std::endl;
            return false;
        }

        unsigned int pos_bytes = position / 8;
        unsigned int pos_bits = position % 8;
        return (d->bytes[pos_bytes] & byte[pos_bits]);
    }

    vector<string> split(string str, char c) {
        vector<string> vec_tokens;
        stringstream ss(str); // Turn the string into a stream.
        string resulted_token;

        while(getline(ss, resulted_token, c)) {
            vec_tokens.push_back(resulted_token);
        }

        return vec_tokens;
    }
}
