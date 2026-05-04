#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include "dialogManager.h"

namespace game{
enum class CHOICE{
    NONE = 0x0,
    GO_HOME = 0x1,
    SKIP_WORK = 0x2,
    WORK = 0x3,
    DEFEND = 0x4,
    NO_DEFEND = 0x5,
    GIVE_UP = 0x6
};

bn::ostringstream& operator<<(bn::ostringstream& os, CHOICE choice);

class GlobalVariables{
private:
    CHOICE day_choices[7] = {CHOICE::NONE,CHOICE::NONE,CHOICE::NONE,CHOICE::NONE,CHOICE::NONE,CHOICE::NONE,CHOICE::NONE};
    unsigned int current_day = 0;
    DialogManager dialog_manager;

    /* Especific room and day information */
    bool visited_work_lab_door = false;
    bool visited_work_hall = false;
    bool roof_checked_day_3 = false;
    bool go_home_day_4A = false;
    bool work_skipped_day_4A = false;
public:
    GlobalVariables() = default;
    ~GlobalVariables() = default;

    DialogManager& getDialogManager();

    CHOICE dayChoice(unsigned int day);
    void setDayChoice(unsigned int day,CHOICE choice);

    /**
     * @brief Returns the variant of the day provided
     * @param day \in [1-6]
     * @return The sum of a and b.
     */
    int getDayVariant(int day);

    unsigned int currentDay();
    void goNextDay();    

    bool hasVisitedLabDoor();
    void setVisitedLabDoor(bool visited);

    bool hasVisitedWorkHall();
    void setVisitedWorkHall(bool visited);

    bool roofCheckedDay3();
    void setRoofCheckedDay3(bool checked);
};
}

#endif