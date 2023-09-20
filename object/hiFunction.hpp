#ifndef HI_FUNCTION_H_
#define HI_FUNCTION_H_

#include "klass.hpp"
#include "hiObject.hpp"
#include "util/map.hpp"
#include "util/arrayList.hpp"

class HiObject;
class CodeObject;

class FunctionKlass : public Klass {
private:
    FunctionKlass() = default;

public:
    static FunctionKlass* get_instance();

    virtual void print(HiObject* obj);
};

class HiFunction : public HiObject {
private:
    CodeObject* _func_code { nullptr };
    HiString* _func_name { nullptr };

    unsigned int _flags { 0 };

    ArrayList<HiObject*>* _defaults { nullptr };

public:
    HiFunction(HiObject* code_object);
    HiFunction(Klass* klass) {
        set_klass(klass);
    }

    HiString* func_name() const { return _func_name; }
    unsigned int flags() const { return _flags; }
    CodeObject* func_code() const { return _func_code; }
    ArrayList<HiObject*>* defaults() const { return _defaults; }
    void set_defaults(ArrayList<HiObject*>* def) {
        _defaults = def;
    }

    void set_globals(Map<HiObject*, HiObject*>* x) { _globals = x; }
    Map<HiObject*, HiObject*>* _globals;
};

#endif  // HI_FUNCTION_H_
