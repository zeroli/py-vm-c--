#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "util/arrayList.hpp"
#include "util/map.hpp"

class CodeObject;
class HiObject;
class FrameObject;

class Interpreter {
public:
    Interpreter();
    ~Interpreter();

    void run(CodeObject* code);

private:
    Map<HiObject*, HiObject*>* _builtins;
    FrameObject* _frame { nullptr };

private:
    void build_frame(HiObject* callable, ArrayList<HiObject*>* args);
    void eval_frame();
    void destroy_frame();
    void leave_frame(HiObject* ret);
};

#endif  // INTERPRETER_H_
