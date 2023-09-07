#include "hiInteger.hpp"
#include "runtime/universe.hpp"

#include <cstdio>

IntegerKlass* IntegerKlass::get_instance() {
    static IntegerKlass klass;
    return &klass;
}

void IntegerKlass::print(HiObject* obj) {
    auto* o = static_cast<HiInteger*>(obj);
    printf("%d", o->value());
}

#define IMPL_COMP_OP(func, op) \
HiObject* IntegerKlass::func(HiObject* x, HiObject* y) { \
    assert(x && x->klass() == this); \
    assert(y && y->klass() == this); \
\
    auto* o1 = static_cast<HiInteger*>(x); \
    auto* o2 = static_cast<HiInteger*>(y); \
\
    return (o1->value() op o2->value()) ? Universe::HiTrue : Universe::HiFalse; \
}

IMPL_COMP_OP(greater, >)
IMPL_COMP_OP(less, <)
IMPL_COMP_OP(equal, ==)
IMPL_COMP_OP(not_equal, !=)
IMPL_COMP_OP(ge, >=)
IMPL_COMP_OP(le, <=)

#undef IMPL_COMP_OP

#define IMPL_ARITH_OP(func, op) \
HiObject* IntegerKlass::func(HiObject* x, HiObject* y) { \
    assert(x && x->klass() == this); \
    assert(y && y->klass() == this); \
\
    auto* o1 = static_cast<HiInteger*>(x); \
    auto* o2 = static_cast<HiInteger*>(y); \
\
    return new HiInteger(o1->value() op o2->value()); \
}

IMPL_ARITH_OP(add, +)
IMPL_ARITH_OP(sub, -)
IMPL_ARITH_OP(mul, *)
IMPL_ARITH_OP(div, /)
IMPL_ARITH_OP(mod, %)

#undef IMPL_ARITH_OP
