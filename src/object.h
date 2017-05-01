/* object.h */

#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <stdint.h>
#include <uuid/uuid.h>

#include "status.h"
#include "data.h"

namespace AngryB {
    class Object {
        private:
            std::string path;
            uint64_t length;
            uint8_t *data;

            void open_file_read(Status *status);

        public:
            Object(uuid_t id, std::string data_dir, Status *status);
            Object(uuid_t id, std::string data_dir, Data *d, Status *status);

            ~Object();

            void get(Data *data);
            uint64_t get_size();
    };
}

#endif // OBJECT_H
