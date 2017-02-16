/* index.h */

#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <uuid/uuid.h>

class Index {
    private:
        std::string path;
    public:
        Index(char *pathname);
        void put();
        void get();
        void del();
};

#endif // INDEX_H
