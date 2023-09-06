#include "hiString.hpp"
#include <cstring>

HiString::HiString(const char* x) {
    _length = strlen(x);
    _value = new char[_length];
    strncpy(_value, x, _length);
}

HiString::HiString(const char* x, int length) {
    _length = length;
    _value = new char[length];
    memcpy(_value, x, length);
}
