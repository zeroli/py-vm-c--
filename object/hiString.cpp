#include "hiString.hpp"
#include "runtime/universe.hpp"
#include "hiInteger.hpp"

#include <cstring>
#include <cstdio>

StringKlass* StringKlass::get_instance() {
    static StringKlass klass;
    return &klass;
}

void StringKlass::print(HiObject* obj) {
    auto* o = static_cast<HiString*>(obj);
    printf("str(%p, %d)", (void*)o->value(), o->length());
}

#define IMPL_COMP_OP(func, op) \
HiObject* StringKlass::func(HiObject* x, HiObject* y) { \
    assert(x && x->klass() == this); \
    assert(y && y->klass() == this); \
\
    auto* o1 = static_cast<HiString*>(x); \
    auto* o2 = static_cast<HiString*>(y); \
\
    return (o1->value() op o2->value() && o1->length() op o2->length())  \
        ? Universe::HiTrue : Universe::HiFalse; \
}

IMPL_COMP_OP(equal, ==)

#undef IMPL_COMP_OP

HiString::HiString(const char* x) {
    _length = strlen(x);
    _value = new char[_length];
    strncpy(_value, x, _length);

    set_klass(StringKlass::get_instance());
}

HiString::HiString(const char* x, int length) {
    _length = length;
    _value = new char[length];
    memcpy(_value, x, length);

    set_klass(StringKlass::get_instance());
}
