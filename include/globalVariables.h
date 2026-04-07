#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include "dialogManager.h"

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

bn::ostringstream& operator<<(bn::ostringstream& os, CHOICE choice);

class GlobalVariables{
private:
    CHOICE day_choices[6] = {CHOICE::NONE,CHOICE::NONE,CHOICE::NONE,CHOICE::NONE,CHOICE::NONE,CHOICE::NONE};
    unsigned int current_day = 0;
    DialogManager dialog_manager;

    bool visited_work_lab_door = false;

public:
    GlobalVariables() = default;
    ~GlobalVariables() = default;

    DialogManager& getDialogManager();

    CHOICE dayChoice(unsigned int day);
    void setDayChoice(unsigned int day,CHOICE choice);

    unsigned int currentDay();
    void goNextDay();    

    bool hasVisitedLabDoor();
    void setVisitedLabDoor(bool visited);
};
}

#endif