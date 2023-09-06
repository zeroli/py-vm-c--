#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "util/arrayList.hpp"

class CodeObject;
class HiObject;

class Interpreter {
public:
    Interpreter();
    ~Interpreter();

    void run(CodeObject* code);

private:
    ArrayList<HiObject*>* _stack;
    ArrayList<HiObject*>* _consts;
    ArrayList<HiObject*>* _names;
};

#endif  // INTERPRETER_H_
