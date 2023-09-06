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

    virtual HiObject* greater(HiObject* x) override;
    virtual HiObject* less(HiObject* x) override;
    virtual HiObject* equal(HiObject* x) override;
    virtual HiObject* not_equal(HiObject* x) override;
    virtual HiObject* ge(HiObject* x) override;
    virtual HiObject* le(HiObject* x) override;
};

#endif  // HI_INTEGER_H_
