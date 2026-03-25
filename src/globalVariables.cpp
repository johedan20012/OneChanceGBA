#include "globalVariables.h"

#include "bn_assert.h"

namespace game{
CHOICE GlobalVariables::dayChoice(unsigned int day){
    BN_ASSERT(1<=day && day<=6,"Invalid day:",day);
    return day_choices[day];
}

void GlobalVariables::setDayChoice(unsigned int day, CHOICE choice){
    BN_ASSERT(1<=day && day<=6,"Invalid day:",day);
    day_choices[day] = choice;
}

unsigned int GlobalVariables::currentDay(){
    BN_ASSERT(1<=current_day && current_day<=6,"Invalid day:",current_day);
    return current_day;
}

void GlobalVariables::goNextDay(){
    current_day += 1;
    BN_ASSERT(1<=current_day && current_day<=6,"Invalid day:",current_day);
}

}