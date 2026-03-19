#ifndef TIMER_H
#define TIMER_H

#define MAX_TIMERS 10

#include "bn_vector.h"

namespace game{
class Timer{
private:
    static bn::vector<Timer*,MAX_TIMERS> timers;

    int frameCount;
public:
    Timer();
    ~Timer();

    int elapsedFrames();
    void restart();

    static void update();
};
}

#endif