#include "binaryFileParser.hpp"

#include "code/codeObject.hpp"
#include "util/bufferInputStream.hpp"
#include "object/hiString.hpp"
#include "object/hiInteger.hpp"

#include <cstdio>
#include <cassert>

BinaryFileParser::BinaryFileParser(BufferedInputStream* stream)
    : file_stream(stream)
{ }

CodeObject* BinaryFileParser::parse() {
    int magic_number = file_stream->read_int();
    printf("magic number is 0x%x\n", magic_number);

    int moddate = file_stream->read_int();
    printf("moddate is 0x%x\n", moddate);

    char object_type = file_stream->read();
    if (object_type == 'c') {
        CodeObject* result = get_code_object();
        printf("parse ok\n");
        return result;
    }

    return nullptr;
}

CodeObject* BinaryFileParser::get_code_object() {
    int argcount = file_stream->read_int();
    printf("argcount: %d\n", argcount);

    int nlocals = file_stream->read_int();
    printf("nlocals: %d\n", nlocals);
    int stacksize = file_stream->read_int();
    printf("stacksize: %d\n", stacksize);
    int flags = file_stream->read_int();
    printf("flags: %d\n", flags);

    HiString* byte_codes = get_byte_codes();
    ArrayList<HiObject*>* consts = get_consts();
    ArrayList<HiObject*>* names = get_names();
    ArrayList<HiObject*>* var_names = get_var_names();
    ArrayList<HiObject*>* free_vars = get_free_vars();
    ArrayList<HiObject*>* cell_vars = get_cell_vars();
    HiString* file_name = get_file_name();
    HiString* module_name = get_module_name();
    int begin_line_no = file_stream->read_int();
    HiString* lnotab = get_lno_table();

    return new CodeObject(
        argcount,
        nlocals,
        stacksize,
        flags,
        byte_codes,
        consts,
        names,
        var_names,
        free_vars,
        cell_vars,
        file_name,
        module_name,
        begin_line_no,
        lnotab
    );
}

HiString* BinaryFileParser::get_byte_codes() {
    assert(file_stream->read() == 's');
    return get_string();
}

HiString* BinaryFileParser::get_string() {
    int length = file_stream->read_int();
    char* str_value = new char[length];
    for (int i = 0; i < length; i++) {
        str_value[i] = file_stream->read();
    }

    HiString* s = new HiString(str_value, length);
    delete[] str_value;

    return s;
}

ArrayList<HiObject*>* BinaryFileParser::get_consts() {
    if (file_stream->read() == '(') {
        return get_tuple();
    }

    file_stream->unread();
    return nullptr;
}

ArrayList<HiObject*>* BinaryFileParser::get_names() {
    if (file_stream->read() == '(') {
        return get_tuple();
    }
    file_stream->unread();
    return nullptr;
}

ArrayList<HiObject*>* BinaryFileParser::get_var_names() {
    if (file_stream->read() == '(') {
        return get_tuple();
    }
    file_stream->unread();
    return nullptr;
}

ArrayList<HiObject*>* BinaryFileParser::get_free_vars() {
    if (file_stream->read() == '(') {
        return get_tuple();
    }
    file_stream->unread();
    return nullptr;
}

ArrayList<HiObject*>* BinaryFileParser::get_cell_vars() {
    if (file_stream->read() == '(') {
        return get_tuple();
    }
    file_stream->unread();
    return nullptr;
}

HiString* BinaryFileParser::get_file_name() {
    assert(file_stream->read() == 's');
    return get_name();
}

HiString* BinaryFileParser::get_module_name() {
    assert(file_stream->read() == 't');
    return get_name();
}

HiString* BinaryFileParser::get_name() {
    return get_string();
}

HiString* BinaryFileParser::get_lno_table() {
    // we found it might be 't' or 's'
    auto c = file_stream->read();
    assert(c == 't' || c == 's');
    return get_string();
}

ArrayList<HiObject*>* BinaryFileParser::get_tuple() {
    int length = file_stream->read_int();
    HiString* str;

    ArrayList<HiObject*>* list = new ArrayList<HiObject*>(length);
    for (int i = 0; i < length; i++) {
        char obj_type = file_stream->read();
        switch (obj_type) {
        case 'c': {
            printf("got a code object\n");
            list->add(get_code_object());
            break;
        }
        case 'i': {
            list->add(new HiInteger(file_stream->read_int()));
            break;
        }
        case 'N': {
            list->add(NULL);
            break;
        }
        case 't': {
            str = get_string();
            list->add(str);
            _string_table.add(str);
            break;
        }
        case 's': {
            list->add(get_string());
            break;
        }
        case 'R': {
            list->add(_string_table.get(file_stream->read_int()));
            break;
        }
        }  // end switch
    }  // end for
    return list;
}
