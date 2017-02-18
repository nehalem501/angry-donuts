/* data.h */

#ifndef DATA_H
#define DATA_H

#include <stdint.h>

struct Data {
    uint8_t *bytes;
    uint64_t length;

    Data();
    Data(uint8_t *b, uint64_t len);
};

#endif // DATA_H
