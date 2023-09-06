#ifndef HI_STRING_H_
#define HI_STRING_H_

#include "hiObject.hpp"

class HiString : public HiObject {
private:
    char* _value;
    int _length;

public:
    HiString(const char* x);
    HiString(const char* x, const int length);
    ~HiString() {
        delete[] _value;
    }

    const char* value() const {
        return _value;
    }
    int length() const {
        return _length;
    }
};

#endif  // HI_STRING_H_
