#include "globalVariables.h"

#include "bn_log.h"
#include "bn_assert.h"

#include "decision_tree_bin.h"

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
    BN_ASSERT(1<=day && day<=7,"Invalid day:",day);
    return day_choices[day-1];
}

void GlobalVariables::setDayChoice(unsigned int day, CHOICE choice){
    BN_ASSERT(1<=day && day<=7,"Invalid day:",day);
    day_choices[day-1] = choice;
}

int GlobalVariables::getDayVariant(int day){
    int row = 0;
    for(int i = 1; i<day; i++){
        BN_ASSERT(size_t(((row*9)+8)) < decision_tree_bin_size,"Skill issue");
        if(day_choices[i-1] == CHOICE::NONE)
        row = decision_tree_bin[row*9 + 2 + 0x1];
        else row = decision_tree_bin[row*9 + 2 + int(day_choices[i-1])];
    }

    //row = decision_tree_bin[row*9 + 2 + int(day_choices[day-1])];

    BN_ASSERT(size_t(((row*9)+8)) < decision_tree_bin_size,"Yep skill issue");
    //if(day <= 5) BN_ASSERT(decision_tree_bin[row*9] == uint8_t(day), "Programming skill issue");
    BN_LOG("Query (",decision_tree_bin[row*9],",",decision_tree_bin[row*9 + 1],")");
    return decision_tree_bin[row*9 + 1];
}

unsigned int GlobalVariables::currentDay(){
    BN_ASSERT(1<=current_day && current_day<=7,"Invalid day:",current_day);
    return current_day;
}

void GlobalVariables::goNextDay(){
    current_day += 1;
    BN_ASSERT(1<=current_day && current_day<=7,"Invalid day:",current_day);
}

bool GlobalVariables::hasVisitedLabDoor(){
    return visited_work_lab_door;
}

void GlobalVariables::setVisitedLabDoor(bool visited){
    visited_work_lab_door = visited;
}

bool GlobalVariables::hasVisitedWorkHall(){
    return visited_work_hall;
}

void GlobalVariables::setVisitedWorkHall(bool visited){
    visited_work_hall = visited;
}

bool GlobalVariables::roofCheckedDay3(){
    return roof_checked_day_3;
}

void GlobalVariables::setRoofCheckedDay3(bool checked){
    roof_checked_day_3 = checked;
}
}