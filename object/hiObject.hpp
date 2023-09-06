#ifndef HI_OBJECT_H_
#define HI_OBJECT_H_

class HiObject {
public:
    virtual ~HiObject() = default;

    virtual void print() { }
    virtual HiObject* add(HiObject* x) { return nullptr; }

    virtual HiObject* greater(HiObject* x) { return nullptr; }
    virtual HiObject* less(HiObject* x) { return nullptr; }
    virtual HiObject* equal(HiObject* x) { return nullptr; }
    virtual HiObject* not_equal(HiObject* x) { return nullptr; }
    virtual HiObject* ge(HiObject* x) { return nullptr; }
    virtual HiObject* le(HiObject* x) { return nullptr; }
};

#endif  // HI_OBJECT_H_
