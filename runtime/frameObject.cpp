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
    _globals = _locals;
    _fast_locals = nullptr;

    _stack = new ArrayList<HiObject*>();
    _loop_stack = new ArrayList<Block*>();

    _codes = codes;
    _pc = 0;
}

FrameObject::FrameObject(HiFunction* func, ObjList* args)
    : FrameObject(func->func_code()) {
    _globals = func->_globals;
    _fast_locals = args;
    // defaults are the last few arguments
    if (func->defaults()) {
        int dft_cnt = func->defaults()->length();
        int argcnt = _codes->_argcount;
        while (dft_cnt--) {
            _fast_locals->set(--argcnt, func->defaults()->get(dft_cnt));
        }
    }
}

FrameObject::~FrameObject() {
    delete _locals;
    delete _fast_locals;
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
