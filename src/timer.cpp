#include "timer.h"

namespace game{
bn::vector<Timer*,MAX_TIMERS> Timer::timers;

Timer::Timer(): frameCount(0){
    timers.push_back(this);
} 

Timer::~Timer(){
    for(auto it = timers.begin(); it!=timers.end(); it++){
        if(*it == this){
            timers.erase(it);
            break;
        }
    }
}

int Timer::elapsedFrames(){
    return frameCount;
}

void Timer::restart(){
    frameCount = 0;
}

void Timer::update(){
    for(auto it = timers.begin(); it!=timers.end(); it++){
        (*it)->frameCount++;
    }
}
}