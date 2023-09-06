#include "hiInteger.hpp"
#include "runtime/universe.hpp"

#include <cstdio>

void HiInteger::print() {
    printf("%d", _value);
}

HiObject* HiInteger::add(HiObject* x) {
    return new HiInteger(_value + ((HiInteger*)x) -> _value);
}

HiObject* HiInteger::greater(HiObject* x) {
    return _value > ((HiInteger*)x) -> _value ? Universe::HiTrue : Universe::HiFalse;
}

HiObject* HiInteger::less(HiObject* x) {
    return _value < ((HiInteger*)x) -> _value ? Universe::HiTrue : Universe::HiFalse;
}

HiObject* HiInteger::equal(HiObject* x) {
    return _value == ((HiInteger*)x) -> _value ? Universe::HiTrue : Universe::HiFalse;
}

HiObject* HiInteger::not_equal(HiObject* x) {
    return _value != ((HiInteger*)x) -> _value ? Universe::HiTrue : Universe::HiFalse;
}

HiObject* HiInteger::ge(HiObject* x) {
    return _value >= ((HiInteger*)x) -> _value ? Universe::HiTrue : Universe::HiFalse;
}

HiObject* HiInteger::le(HiObject* x) {
    return _value <= ((HiInteger*)x) -> _value ? Universe::HiTrue : Universe::HiFalse;
}
