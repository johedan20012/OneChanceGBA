#ifndef ANIMATION_H
#define ANIMATION_H

namespace game{

class Animation{
protected:
    unsigned int state = 0;

public:
    virtual ~Animation() = default;

    virtual void update() = 0;

    virtual bool isFinished() = 0;
};
}

#endif