#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include "bn_unique_ptr.h"

namespace game{
enum class CHOICE{
    NONE,
    WORK,
    SKIP_WORK,
    GO_HOME,
    DEFEND,
    NO_DEFEND,
    GIVE_UP
};

namespace GlobalVariables{
namespace{
    CHOICE day_choices[6] = {CHOICE::NONE,CHOICE::NONE,CHOICE::NONE,CHOICE::NONE,CHOICE::NONE,CHOICE::NONE};
    unsigned int current_day = 0;
}

CHOICE dayChoice(unsigned int day);
void setDayChoice(unsigned int day,CHOICE choice);

unsigned int currentDay();
void goNextDay();
};
}

#endif