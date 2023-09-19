#ifndef FRAME_OBJECT_H_
#define FRAME_OBJECT_H_

#include "util/arrayList.hpp"
#include "util/map.hpp"

class CodeObject;
class HiObject;
class HiFunction;
class Block;

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

class FrameObject {
public:
    explicit FrameObject(CodeObject* codes);
    explicit FrameObject(HiFunction* func);

    ~FrameObject();

    FrameObject* _sender { nullptr };

    void set_sender(FrameObject* x) { _sender = x; }
    FrameObject* sender() const { return _sender; }
    bool is_first_frame() const { return _sender == nullptr; }

    ArrayList<HiObject*>* _stack;
    ArrayList<Block*>* _loop_stack;
    ArrayList<HiObject*>* _consts;
    ArrayList<HiObject*>* _names;
    Map<HiObject*, HiObject*>* _locals;
    Map<HiObject*, HiObject*>* _globals;

    CodeObject* _codes;
    int _pc;

public:
    void set_pc(int pc) { _pc = pc; }
    int get_pic() const { return _pc; }

    ArrayList<HiObject*>* stack() const { return _stack; }
    ArrayList<Block*>* loop_stack() const { return _loop_stack; }
    ArrayList<HiObject*>* consts() const { return _consts; }
    ArrayList<HiObject*>* names() const { return _names; }
    Map<HiObject*, HiObject*>* locals() const { return _locals; }
    Map<HiObject*, HiObject*>* globals() const { return _globals; }

    bool has_more_codes() const;
    unsigned char get_op_code();
    int get_op_arg();

    int jump_by(int offset) {
        return _pc += offset;
    }
    int jump_to(int pc) {
        return _pc = pc;
    }
    int current_pc() const {
        return _pc;
    }
};

#endif  // FRAME_OBJECT_H_
