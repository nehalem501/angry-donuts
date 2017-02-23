/* data.cpp */

#include <stdlib.h>
#include <stdint.h>

#include "data.h"

Data::Data() : bytes(NULL),
               length(0) {
}

Data::Data(uint8_t *b, uint64_t len) : bytes(b),
                                       length(len) {
}
