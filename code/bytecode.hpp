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
        COMPARE_OP = 107,
        JUMP_FORWARD = 110,
        POP_JUMP_IF_FALSE = 114,
    };
};

enum COMPARE {
    LESS = 0,
    LESS_EQUAL,
    EQUAL,
    NOT_EQUAL,
    GREATER,
    GREATER_EQUAL,
};


#endif  // BYTECODE_H_
