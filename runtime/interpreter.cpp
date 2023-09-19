#include "interpreter.hpp"

#include "code/codeObject.hpp"
#include "util/arrayList.hpp"
#include "code/bytecode.hpp"
#include "object/hiString.hpp"
#include "object/hiInteger.hpp"
#include "object/hiFunction.hpp"
#include "runtime/universe.hpp"
#include "runtime/frameObject.hpp"

#include <cassert>

#define PUSH(x) _frame->_stack->add(x)
#define POP() _frame->_stack->pop()
#define STACK_LEVEL() _frame->_stack->size()
#define LOG_BYTECODE(x) printf(" ->%s\n", ByteCode::Str(x))


#define HI_TRUE Universe::HiTrue
#define HI_FALSE Universe::HiFalse

Interpreter::Interpreter()
{
    Universe::genesis();
}

Interpreter::~Interpreter() {
    delete _builtins;
    delete _frame;
    Universe::destroy();
}

void Interpreter::run(CodeObject* codes)
{
    printf("\npython interpeter starts...\n");
    _builtins = new Map<HiObject*, HiObject*>();
    _builtins->put(new HiString("True"), Universe::HiTrue);
    _builtins->put(new HiString("False"), Universe::HiFalse);
    _builtins->put(new HiString("None"), Universe::HiNone);

    _frame = new FrameObject(codes);

    eval_frame();
    destroy_frame();

    printf("\npython interpeter ends...\n");
}

void Interpreter::build_frame(HiObject* callable) {
    auto* frame = new FrameObject(static_cast<HiFunction*>(callable));
    frame->set_sender(_frame);
    _frame = frame;
}

void Interpreter::eval_frame() {
    while (_frame->has_more_codes()) {
        auto op_code = _frame->get_op_code();
        bool has_argument = (op_code & 0xFF) >= ByteCode::HAVE_ARGUMENT;

        int op_arg = -1;
        if (has_argument) {
            op_arg = _frame->get_op_arg();
        }

        HiObject *v, *w, *u, *attr;

        LOG_BYTECODE(op_code);

        switch (op_code) {
            case ByteCode::POP_TOP: {
                POP();
                break;
            }
            case ByteCode::INPLACE_ADD: {
                w = POP();
                v = POP();
                PUSH(v->add(w));
                break;
            }
            case ByteCode::STORE_NAME: {
                v = _frame->names()->get(op_arg);
                _frame->locals()->put(v, POP());
                break;
            }
            case ByteCode::LOAD_CONST: {
                PUSH(_frame->consts()->get(op_arg));
                break;
            }
            case ByteCode::LOAD_NAME: {
                v = _frame->names()->get(op_arg);
                w = _frame->locals()->get(v);
                if (w != Universe::HiNone) {
                    PUSH(w);
                    break;
                }
                w = _frame->globals()->get(v);
                if (w != Universe::HiNone) {
                    PUSH(w);
                    break;
                }
                w = _builtins->get(v);
                if (w != Universe::HiNone) {
                    PUSH(w);
                    break;
                }
                PUSH(Universe::HiNone);
                break;
            }
            case ByteCode::PRINT_ITEM: {
                v = POP();
                v->print();
                break;
            }
            case ByteCode::PRINT_NEWLINE: {
                printf("\n");
                break;
            }
            case ByteCode::BINARY_ADD: {
                w = POP();
                v = POP();
                PUSH(v->add(w));
                break;
            }
            case ByteCode::COMPARE_OP: {
                w = POP();
                v = POP();

                switch (op_arg) {
                    case IS: {
                        if (v == w) {
                            PUSH(HI_TRUE);
                        } else {
                            PUSH(HI_FALSE);
                        }
                        break;
                    }
                    case IS_NOT: {
                        if (v == w) {
                            PUSH(HI_FALSE);
                        } else {
                            PUSH(HI_TRUE);
                        }
                        break;
                    }
                    case GREATER: {
                        PUSH(v->greater(w));
                        break;
                    }
                    case LESS: {
                        PUSH(v->less(w));
                        break;
                    }
                    case EQUAL: {
                        PUSH(v->equal(w));
                        break;
                    }
                    case NOT_EQUAL: {
                        PUSH(v->not_equal(w));
                        break;
                    }
                    case GREATER_EQUAL: {
                        PUSH(v->ge(w));
                        break;
                    }
                    case LESS_EQUAL: {
                        PUSH(v->le(w));
                        break;
                    }
                    default: {
                        printf("Error: Unrecognized compare op %d\n", op_arg);
                        assert(0);
                    }
                }
                break;
            }
            case ByteCode::POP_JUMP_IF_FALSE: {
                v = POP();
                if (v == Universe::HiFalse) {
                    _frame->jump_to(op_arg);
                }
                break;
            }
            case ByteCode::JUMP_FORWARD: {
                _frame->jump_by(op_arg);
                break;
            }
            case ByteCode::JUMP_ABSOLUTE: {
                _frame->jump_to(op_arg);
                break;
            }
            case ByteCode::SETUP_LOOP: {
                _frame->loop_stack()->add(new Block(
                    op_code, _frame->current_pc() + op_arg,
                    STACK_LEVEL())
                );
                break;
            }
            case ByteCode::POP_BLOCK: {
                auto b = _frame->loop_stack()->pop();
                while (STACK_LEVEL() > b->_level) {
                    POP();
                }
                break;
            }
            case ByteCode::BREAK_LOOP: {
                auto b = _frame->loop_stack()->pop();
                while (STACK_LEVEL() > b->_level) {
                    POP();
                }
                _frame->jump_to(b->_target);
                break;
            }
            case ByteCode::MAKE_FUNCTION: {
                v = POP();
                auto* fo = new HiFunction(v);
                fo->set_globals(_frame->globals());
                PUSH(fo);
                break;
            }
            case ByteCode::CALL_FUNCTION: {
                v = POP();
                build_frame(v);
                break;
            }
            case ByteCode::RETURN_VALUE: {
                v = POP();
                if (_frame->is_first_frame()) {
                    return;
                }
                leave_frame(v);
                break;
            }
            default: {
                printf("Error: Unrecognized byte code: %d\n", op_code);
                assert(0);
            }
        }
    }
}

void Interpreter::destroy_frame() {
    auto* sender = _frame->sender();
    delete _frame;
    _frame = sender;
}

void Interpreter::leave_frame(HiObject* ret) {
    destroy_frame();
    PUSH(ret);
}
