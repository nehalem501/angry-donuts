/* index.h */

#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <uuid/uuid.h>

#include "status.h"
#include "data.h"

class Index {
    private:
        std::string path;
    public:
        Index(char *pathname);
        Index(std::string pathname);

        Status put(uuid_t returned_id, Data *data);
        Status get(uuid_t id, Data *data);
        Status del(uuid_t id);
};

#endif // INDEX_H
