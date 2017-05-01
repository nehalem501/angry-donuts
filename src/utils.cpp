/* utils.cpp */

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
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
    }

    Data* get_index_data(std::string path) {
        return NULL;
    }

    void set(uint8_t *array, unsigned int length, unsigned int position, bool value) {
        if (position >= length * 8) {
            std::cout << "error: set: position greater than length of array" << std::endl;
            return;
        }

        unsigned int pos_bytes = position / 8;
        unsigned int pos_bits = position % 8;

        if (value) {
            array[pos_bytes] = array[pos_bytes] | byte[pos_bits];
        } else {
            array[pos_bytes] = array[pos_bytes] & ~byte[pos_bits];
        }
    }

    bool get(uint8_t *array, unsigned int length, unsigned int position) {
        if (position >= length * 8) {
            std::cout << "error: get: position greater than length of array" << std::endl;
            return false;
        }

        unsigned int pos_bytes = position / 8;
        unsigned int pos_bits = position % 8;
        return (array[pos_bytes] & byte[pos_bits]);
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
/*
// Creer l'arborescence de dossier object_path à partir d'une racine root_path
void create_path(string root_path, string object_path) {
	char char_splitter = '/';
	vector<string> v = splitStringToVector(object_path,char_splitter);
	string fil_dAriane = root_path;
	for(string s : v){
		fil_dAriane += char_splitter + s;
		mkdir(fil_dAriane.c_str(), ACCESSPERMS);
	}
}*/

