#include "util/bufferInputStream.hpp"

#include <cstdlib>

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("vm need a parameter: filename\n");
        exit(-1);
    }

    BufferedInputStream stream(argv[1]);
    printf("magic number is 0x%x\n", stream.read_int());

    return 0;
}
