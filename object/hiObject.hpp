#ifndef HI_OBJECT_H_
#define HI_OBJECT_H_

#include <cassert>

class Klass;

class HiObject {
private:
    Klass* _klass = nullptr;

public:
    Klass* klass() {
        assert(_klass != nullptr);
        return _klass;
    }
    void set_klass(Klass* klass) {
        _klass = klass;
    }

    void print();

    #define DECL_BINARY_OP(func) \
        HiObject* func(HiObject* x)

    DECL_BINARY_OP(add);
    DECL_BINARY_OP(sub);
    DECL_BINARY_OP(mul);
    DECL_BINARY_OP(div);
    DECL_BINARY_OP(mod);
    DECL_BINARY_OP(greater);
    DECL_BINARY_OP(less);
    DECL_BINARY_OP(equal);
    DECL_BINARY_OP(not_equal);
    DECL_BINARY_OP(ge);
    DECL_BINARY_OP(le);

    #undef DECL_BINARY_OP
};

#endif  // HI_OBJECT_H_
