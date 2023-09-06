#ifndef CODE_OBJECT_H_
#define CODE_OBJECT_H_

#include "util/arrayList.hpp"
#include "object/hiObject.hpp"

class HiString;

class CodeObject : public HiObject {
public:
    CodeObject(int argcount, int nlocals, int stack_size, int flag,
        HiString* bytecode,
        ArrayList<HiObject*>* consts,
        ArrayList<HiObject*>* names,
        ArrayList<HiObject*>* varnames,
        ArrayList<HiObject*>* free_names,
        ArrayList<HiObject*>* cell_names,
        HiString* file_name,
        HiString* module_name,
        int begin_line_no,
        HiString* lnotab)
        : _argcount(argcount)
        , _nlocals(nlocals)
        , _stack_size(stack_size)
        , _flag(flag)
        , _bytecode(bytecode)
        , _consts(consts)
        , _names(names)
        , _varnames(varnames)
        , _file_name(file_name)
        , _module_name(module_name)
        , _begin_line_no(begin_line_no)
        , _lnotab(lnotab)
    { }

private:
    int _argcount;
    int _nlocals;
    int _stack_size;
    int _flag;
    HiString* _bytecode;
    ArrayList<HiObject*>* _names;
    ArrayList<HiObject*>* _consts;
    ArrayList<HiObject*>* _varnames;
    ArrayList<HiObject*>* _free_names;
    ArrayList<HiObject*>* _cell_names;
    HiString* _file_name;
    HiString* _module_name;
    int _begin_line_no;
    HiString* _lnotab;
};

#endif  // CODE_OBJECT_H_
