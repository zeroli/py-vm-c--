#include "hiInteger.hpp"

#include <cstdio>

void HiInteger::print() {
    printf("%d", _value);
}

HiObject* HiInteger::add(HiObject* x) {
    return new HiInteger(_value + ((HiInteger*)x) -> _value);
}

HiObject* HiInteger::greater(HiObject* x) {
    return new HiInteger(_value > ((HiInteger*)x) -> _value);
}

HiObject* HiInteger::less(HiObject* x) {
    return new HiInteger(_value < ((HiInteger*)x) -> _value);
}

HiObject* HiInteger::equal(HiObject* x) {
    return new HiInteger(_value == ((HiInteger*)x) -> _value);
}

HiObject* HiInteger::not_equal(HiObject* x) {
    return new HiInteger(_value != ((HiInteger*)x) -> _value);
}

HiObject* HiInteger::ge(HiObject* x) {
    return new HiInteger(_value >= ((HiInteger*)x) -> _value);
}

HiObject* HiInteger::le(HiObject* x) {
    return new HiInteger(_value <= ((HiInteger*)x) -> _value);
}
