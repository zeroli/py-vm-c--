#ifndef HI_STRING_H_
#define HI_STRING_H_

#include "hiObject.hpp"
#include "klass.hpp"

class StringKlass : public Klass {
private:
    StringKlass() = default;

public:
    static StringKlass* get_instance();

    virtual void print(HiObject* obj) override;

    #define DECL_BINARY_OP(func) \
        virtual HiObject* func(HiObject* x, HiObject* y) override

    DECL_BINARY_OP(equal);

    #undef DECL_BINARY_OP
};

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
