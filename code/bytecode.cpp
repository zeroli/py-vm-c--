#include "bytecode.hpp"

#include <map>

const char* ByteCode::Str(int bytecode)
{
    #define _ENTRY(code) { code, #code }

    static std::map<int, const char*> bc = {
        _ENTRY(POP_TOP),
        _ENTRY(BINARY_ADD),
        _ENTRY(INPLACE_ADD),
        _ENTRY(PRINT_ITEM),
        _ENTRY(PRINT_NEWLINE),
        _ENTRY(BREAK_LOOP),
        _ENTRY(RETURN_VALUE),
        _ENTRY(POP_BLOCK),

        //_ENTRY(HAVE_ARGUMENT),
        _ENTRY(STORE_NAME),
        _ENTRY(LOAD_CONST),
        _ENTRY(LOAD_NAME),
        _ENTRY(COMPARE_OP),
        _ENTRY(JUMP_FORWARD),
        _ENTRY(JUMP_ABSOLUTE),
        _ENTRY(POP_JUMP_IF_FALSE),
        _ENTRY(SETUP_LOOP),
        _ENTRY(LOAD_FAST),
        _ENTRY(CALL_FUNCTION),
        _ENTRY(MAKE_FUNCTION),
    };
    #undef _ENTRY
    return bc[bytecode];
}
