#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "util/arrayList.hpp"

class CodeObject;
class HiObject;

class Interpreter {
public:
    Interpreter() = default;
    ~Interpreter() {
        delete _stack;
    }

    void run(CodeObject* code);

private:
    ArrayList<HiObject*>* _stack;
    ArrayList<HiObject*>* _consts;

};

#endif  // INTERPRETER_H_
