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

    /* Especific room and day information */
    bool visited_work_lab_door = false;
    bool roof_checked_day_3 = false;
    bool work_skipped_day_4A = false;
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

    bool roofCheckedDay3();
    void setRoofCheckedDay3(bool checked);

    bool workSkippedDay4A();
    void setWorkSkippedDay4A(bool skipped);
};
}

#endif