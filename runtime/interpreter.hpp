#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "util/arrayList.hpp"

class CodeObject;
class HiObject;

class Block {
public:
    unsigned char _type;
    unsigned int _target;
    int _level;

    Block(unsigned char b_type,
            unsigned int b_target,
            int b_level)
        : _type(b_type), _target(b_target)
        , _level(b_level)
    { }
};

class Interpreter {
public:
    Interpreter();
    ~Interpreter();

    void run(CodeObject* code);

private:
    ArrayList<Block*>* _loop_stack;

    ArrayList<HiObject*>* _stack;
    ArrayList<HiObject*>* _consts;
    ArrayList<HiObject*>* _names;
};

#endif  // INTERPRETER_H_
