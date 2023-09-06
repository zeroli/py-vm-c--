#ifndef HI_INTEGER_H_
#define HI_INTEGER_H_

#include "hiObject.hpp"

class HiInteger : public HiObject {
private:
    int _value;

public:
    HiInteger(int x) : _value(x) { }
    int value() const { return _value; }

    virtual void print() override;

    virtual HiObject* add(HiObject* x) override;
};

#endif  // HI_INTEGER_H_
