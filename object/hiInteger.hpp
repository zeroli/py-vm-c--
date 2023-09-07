#ifndef HI_INTEGER_H_
#define HI_INTEGER_H_

#include "hiObject.hpp"
#include "klass.hpp"

class IntegerKlass;

class IntegerKlass : public Klass {
private:
    IntegerKlass() = default;
public:
    static IntegerKlass* get_instance();

    virtual void print(HiObject* obj) override;

    #define DECL_BINARY_OP(func) \
        virtual HiObject* func(HiObject* x, HiObject* y) override

    DECL_BINARY_OP(greater);
    DECL_BINARY_OP(less);
    DECL_BINARY_OP(equal);
    DECL_BINARY_OP(not_equal);
    DECL_BINARY_OP(ge);
    DECL_BINARY_OP(le);

    DECL_BINARY_OP(add);
    DECL_BINARY_OP(sub);
    DECL_BINARY_OP(mul);
    DECL_BINARY_OP(div);
    DECL_BINARY_OP(mod);

    #undef DECL_BINARY_OP
};

class HiInteger : public HiObject {
private:
    int _value;

public:
    HiInteger(int x) : _value(x) {
        set_klass(IntegerKlass::get_instance());
     }

    int value() const { return _value; }
};

#endif  // HI_INTEGER_H_
