#ifndef UNIVERSE_H_
#define UNIVERSE_H_

class HiInteger;
class HiObject;

class Universe {
public:
    static HiInteger* HiTrue;
    static HiInteger* HiFalse;

    static HiObject* HiNone;

    static void genesis();
    static void destroy();
};

#endif  // UNIVERSE_H_
