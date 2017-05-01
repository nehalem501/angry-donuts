/* index.h */

#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <list>
#include <uuid/uuid.h>
#include <stdint.h>

#include "status.h"
#include "data.h"
#include "object.h"

namespace AngryB {
    struct Entry {
        uuid_t id;
        Object *object;
        int nb_opened;
    };
    
    class Index {
        private:
            std::string path;
            std::list<Entry*> m_index;

            Entry* get_entry(uuid_t id);
            void add_entry(Entry *e);
            
            void add(uuid_t id);
            bool exists(uuid_t id);

        public:
            Index(char *pathname);
            Index(std::string pathname);

            Status put(uuid_t id, Data *data);
            Status get(uuid_t id, Data *data);
            Status del(uuid_t id);

            int64_t get_size(uuid_t id);
    };
}

#endif // INDEX_H
