#include "hiObject.hpp"

#include "klass.hpp"

void HiObject::print() {
    klass()->print(this);
}

#define IMPL_BINARY_OP(func) \
HiObject* HiObject::func(HiObject* x) { \
    return klass()->func(this, x); \
}

IMPL_BINARY_OP(add);
IMPL_BINARY_OP(sub);
IMPL_BINARY_OP(mul);
IMPL_BINARY_OP(div);
IMPL_BINARY_OP(mod);

IMPL_BINARY_OP(greater);
IMPL_BINARY_OP(less);
IMPL_BINARY_OP(equal);
IMPL_BINARY_OP(not_equal);
IMPL_BINARY_OP(ge);
IMPL_BINARY_OP(le);

#undef IMPL_BINARY_OP
