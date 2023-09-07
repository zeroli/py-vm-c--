#include "hiFunction.hpp"

#include "code/codeObject.hpp"

#include <cassert>

FunctionKlass* FunctionKlass::get_instance() {
    static FunctionKlass klass;
    return &klass;
}

void FunctionKlass::print(HiObject* obj) {
    printf("<function: ");
    assert(obj && obj->klass() == this);
    auto* o = static_cast<HiFunction*>(obj);
    o->print();
    printf(">");
}

HiFunction::HiFunction(HiObject* code_object) {
    CodeObject* co = static_cast<CodeObject*>(code_object);

    _func_code = co;
    _func_name = co->_module_name; // FIXME:
    _flags = co->_flag;
    set_klass(FunctionKlass::get_instance());
}
