#include "globalVariables.h"

#include "bn_assert.h"

namespace game{

bn::ostringstream& operator<<(bn::ostringstream& os, CHOICE choice){
    switch (choice){
    case CHOICE::WORK:
        return os << "Work";
        break;
    case CHOICE::SKIP_WORK:
        return os << "Skip work";
        break;
    case CHOICE::GO_HOME:
        return os << "Go home";
        break;
    case CHOICE::DEFEND:
        return os << "Defend";
        break;
    case CHOICE::NO_DEFEND:
        return os << "No defend";
        break;
    case CHOICE::GIVE_UP:
        return os << "Give up";
        break;
    default:
        return os << "None";
        break;
    }
}

DialogManager& GlobalVariables::getDialogManager(){
    return dialog_manager;
}

CHOICE GlobalVariables::dayChoice(unsigned int day){
    BN_ASSERT(1<=day && day<=6,"Invalid day:",day);
    return day_choices[day-1];
}

void GlobalVariables::setDayChoice(unsigned int day, CHOICE choice){
    BN_ASSERT(1<=day && day<=6,"Invalid day:",day);
    day_choices[day-1] = choice;
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