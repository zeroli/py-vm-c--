#ifndef BYTECODE_H_
#define BYTECODE_H_

#include <cstdint>

struct ByteCode {
    enum {
        POP_TOP = 1,
        BINARY_ADD = 23,
        INPLACE_ADD = 55,
        PRINT_ITEM = 71,
        PRINT_NEWLINE = 72,
        BREAK_LOOP = 80,
        RETURN_VALUE = 83,
        POP_BLOCK = 87,

        HAVE_ARGUMENT = 90,
        STORE_NAME = 90,
        LOAD_CONST = 100,
        LOAD_NAME = 101,
        COMPARE_OP = 107,
        JUMP_FORWARD = 110,
        JUMP_ABSOLUTE = 113,
        POP_JUMP_IF_FALSE = 114,
        SETUP_LOOP = 120,
        LOAD_FAST = 124,
        CALL_FUNCTION = 131,
        MAKE_FUNCTION = 132,
    };

    static const char* Str(int bytecode);
};

enum COMPARE {
    LESS = 0,
    LESS_EQUAL,
    EQUAL,
    NOT_EQUAL,
    GREATER,
    GREATER_EQUAL,
    IS = 8,
    IS_NOT,
};


#endif  // BYTECODE_H_
