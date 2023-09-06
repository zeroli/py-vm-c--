#include "universe.hpp"

#include "object/hiInteger.hpp"

HiInteger* Universe::HiTrue = nullptr;
HiInteger* Universe::HiFalse = nullptr;

HiObject* Universe::HiNone = nullptr;

void Universe::genesis() {
    HiTrue = new HiInteger(1);
    HiFalse = new HiInteger(0);
    HiNone = new HiObject();
}

void Universe::destroy() {
    delete HiTrue;
    delete HiFalse;
    delete HiNone;
}
