/* data.cpp */

#include <stdlib.h>
#include <stdint.h>

#include "data.h"

using namespace AngryB;

Data::Data() : bytes(NULL),
               length(0) {
}

Data::Data(uint8_t *b, uint64_t len) : bytes(b),
                                       length(len) {
}
