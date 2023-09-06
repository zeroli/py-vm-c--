#ifndef HI_OBJECT_H_
#define HI_OBJECT_H_

class HiObject {
public:
    virtual void print() { }
    virtual HiObject* add(HiObject* x) { return nullptr; }
};

#endif  // HI_OBJECT_H_
