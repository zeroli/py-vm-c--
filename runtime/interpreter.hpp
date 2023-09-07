#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "util/arrayList.hpp"

class CodeObject;
class HiObject;
class FrameObject;

class Interpreter {
public:
    Interpreter();
    ~Interpreter();

    void run(CodeObject* code);

private:
    FrameObject* _frame { nullptr };

private:
    void build_frame(HiObject* callable);
    void eval_frame();
    void destroy_frame();
    void leave_frame(HiObject* ret);
};

#endif  // INTERPRETER_H_
