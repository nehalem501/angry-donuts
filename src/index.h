/* index.h */

#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <uuid/uuid.h>
#include <stdint.h>

#include "status.h"
#include "data.h"

namespace AngryB {
    class Index {
        private:
            std::string path;
        public:
            Index(char *pathname);
            Index(std::string pathname);

            Status put(uuid_t returned_id, Data *data);
            Status get(uuid_t id, Data *data);
            Status del(uuid_t id);

            int64_t get_size(uuid_t id);
    };
}

#endif // INDEX_H
