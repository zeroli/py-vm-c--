#ifndef KLASS_H_
#define KLASS_H_

class HiString;
class HiObject;

class Klass {
private:
    HiString* _name;

public:
    Klass() = default;

    void set_name(HiString* x) { _name = x; }
    HiString* get_name() const { return _name; }

    virtual void print(HiObject* obj) { }

    #define DEF_BINARY_OP(func) \
        virtual HiObject* func(HiObject* x, HiObject* y) { return nullptr; }

    DEF_BINARY_OP(greater);
    DEF_BINARY_OP(less);
    DEF_BINARY_OP(equal);
    DEF_BINARY_OP(not_equal);
    DEF_BINARY_OP(ge);
    DEF_BINARY_OP(le);
    DEF_BINARY_OP(add);
    DEF_BINARY_OP(sub);
    DEF_BINARY_OP(mul);
    DEF_BINARY_OP(div);
    DEF_BINARY_OP(mod);

    #undef DEF_BINARY_OP
};

#endif // KLASS_H_
