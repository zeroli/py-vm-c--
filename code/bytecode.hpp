#ifndef BYTECODE_H_
#define BYTECODE_H_

#include <cstdint>

struct ByteCode {
    enum {
        BINARY_ADD = 23,

        PRINT_ITEM = 71,
        PRINT_NEWLINE = 72,
        RETURN_VALUE = 83,

        HAVE_ARGUMENT = 90,
        LOAD_CONST = 100,
    };
};

#endif  // BYTECODE_H_
