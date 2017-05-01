/* index.h */

#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <vector>
#include <uuid/uuid.h>

#include "status.h"
#include "data.h"

class Index {
    private:
        std::string path;
        std::vector<uuid_t> m_index;
        
        bool exists(uuid_t id);
        
    public:
        Index(char *pathname);

        Status put(uuid_t id, Data *data);
        Status get(uuid_t id, Data *data);
        Status del(uuid_t id);
};

#endif // INDEX_H
