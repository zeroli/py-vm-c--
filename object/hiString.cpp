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
    printf("str(0x%p, %d)", (void*)o->value(), o->length());
}

HiObject* StringKlass::equal(HiObject* x, HiObject* y) { \
    assert(x && x->klass() == this); \
    assert(y && y->klass() == this); \
\
    auto* o1 = static_cast<HiString*>(x); \
    auto* o2 = static_cast<HiString*>(y); \
\
    if (o1->length() != o2->length())  \
        return Universe::HiFalse; \
    return memcmp(o1->value(), o2->value(), o1->length()) == 0 ? \
        Universe::HiTrue : Universe::HiFalse;  \
}

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
