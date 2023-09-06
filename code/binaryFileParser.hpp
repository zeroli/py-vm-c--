#ifndef BINARY_FILE_PARSER_H_
#define BINARY_FILE_PARSER_H_

#include "util/arrayList.hpp"

class CodeObject;
class BufferedInputStream;
class HiObject;
class HiString;

class BinaryFileParser {
private:
    BufferedInputStream* file_stream;
    ArrayList<HiString*> _string_table;  // string intern table
public:
    explicit BinaryFileParser(BufferedInputStream* stream);

    CodeObject* parse();

private:
    CodeObject* get_code_object();

    HiString* get_byte_codes();

    ArrayList<HiObject*>* get_consts();
    ArrayList<HiObject*>* get_names();
    ArrayList<HiObject*>* get_var_names();
    ArrayList<HiObject*>* get_free_vars();
    ArrayList<HiObject*>* get_cell_vars();
    HiString* get_file_name();
    HiString* get_name();

    HiString* get_lno_table();

    HiString* get_string();
    ArrayList<HiObject*>* get_tuple();
};

#endif  // BINARY_FILE_PARSER_H_
