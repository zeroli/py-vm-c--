#include "interpreter.hpp"

#include "code/codeObject.hpp"
#include "util/arrayList.hpp"
#include "code/bytecode.hpp"
#include "object/hiString.hpp"
#include "object/hiInteger.hpp"
#include "runtime/universe.hpp"

#include <cassert>

#define PUSH(x) _stack->add(x)
#define POP() _stack->pop()
#define STACK_LEVEL() _stack->size()
#define LOG_BYTECODE(x) printf(" ->%s\n", ByteCode::Str(x))

Interpreter::Interpreter()
{
    Universe::genesis();
}

Interpreter::~Interpreter() {
    delete _stack;
    Universe::destroy();
}

void Interpreter::run(CodeObject* codes)
{
    printf("\npython interpeter starts...\n");
    _loop_stack = new ArrayList<Block*>();

    int pc = 0;
    int code_length = codes->_bytecodes->length();

    _stack = new ArrayList<HiObject*>(codes->_stack_size);
    _consts = codes->_consts;
    _names = codes->_names;

    while (pc < code_length) {
        unsigned char op_code = codes->_bytecodes->value()[pc++];
        bool has_argument = (op_code & 0xFF) >= ByteCode::HAVE_ARGUMENT;

        int op_arg = -1;
        if (has_argument) {
            int byte1 = (codes->_bytecodes->value()[pc++] & 0xFF);
            op_arg = ((codes->_bytecodes->value()[pc++] & 0xFF) << 8) | byte1;
        }
        HiInteger *lhs, *rhs;
        HiObject *v, *w, *u, *attr;

        LOG_BYTECODE(op_code);

        switch (op_code) {
            case ByteCode::INPLACE_ADD: {
                w = POP();
                v = POP();
                PUSH(v->add(w));
                break;
            }
            case ByteCode::STORE_NAME: {
                v = POP();
                _names->set(op_arg, v);
                break;
            }
            case ByteCode::LOAD_CONST: {
                PUSH(_consts->get(op_arg));
                break;
            }
            case ByteCode::LOAD_NAME: {
                PUSH(_names->get(op_arg));
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
            case ByteCode::RETURN_VALUE: {
                POP();
                break;
            }
            case ByteCode::COMPARE_OP: {
                w = POP();
                v = POP();

                switch (op_arg) {
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
                    pc = op_arg;
                }
                break;
            }
            case ByteCode::JUMP_FORWARD: {
                pc += op_arg;
                break;
            }
            case ByteCode::JUMP_ABSOLUTE: {
                pc = op_arg;
                break;
            }
            case ByteCode::SETUP_LOOP: {
                _loop_stack->add(new Block(
                    op_code, pc + op_arg,
                    STACK_LEVEL())
                );
                break;
            }
            case ByteCode::POP_BLOCK: {
                auto b = _loop_stack->pop();
                while (STACK_LEVEL() > b->_level) {
                    POP();
                }
                break;
            }
            case ByteCode::BREAK_LOOP: {
                auto b = _loop_stack->pop();
                while (STACK_LEVEL() > b->_level) {
                    POP();
                }
                pc = b->_target;
                break;
            }
            default: {
                printf("Error: Unrecognized byte code: %d\n", op_code);
                assert(0);
            }
        }
    }

    printf("\npython interpeter ends...\n");
}
