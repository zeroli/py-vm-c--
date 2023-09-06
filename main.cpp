#include "util/bufferInputStream.hpp"
#include "code/binaryFileParser.hpp"
#include "code/codeObject.hpp"

#include <cstdlib>

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("vm need a parameter: filename\n");
        exit(-1);
    }

    BufferedInputStream stream(argv[1]);
    BinaryFileParser parser(&stream);
    CodeObject* main_code = parser.parse();

    return 0;
}
