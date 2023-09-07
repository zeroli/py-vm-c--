#include "frameObject.hpp"

#include "code/codeObject.hpp"
#include "code/bytecode.hpp"
#include "object/hiObject.hpp"
#include "object/hiString.hpp"
#include "object/hiFunction.hpp"

FrameObject::FrameObject(CodeObject* codes) {
    _consts = codes->_consts;
    _names = codes->_names;

    _locals = new Map<HiObject*, HiObject*>();
    _stack = new ArrayList<HiObject*>();
    _loop_stack = new ArrayList<Block*>();

    _codes = codes;
    _pc = 0;
}

FrameObject::FrameObject(HiFunction* func)
    : FrameObject(func->func_code()) {
}

FrameObject::~FrameObject() {
    delete _locals;
    delete _stack;
    delete _loop_stack;
}

bool FrameObject::has_more_codes() const {
    return _pc < _codes->_bytecodes->length();
}

unsigned char FrameObject::get_op_code() {
    return _codes->_bytecodes->value()[_pc++];
}

int FrameObject::get_op_arg() {
    int byte1 = (_codes->_bytecodes->value()[_pc++] & 0xFF);
    return ((_codes->_bytecodes->value()[_pc++] & 0xFF) << 8) | byte1;
}