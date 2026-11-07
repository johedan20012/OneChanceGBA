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

constexpr bn::string_view choice_to_string(CHOICE choice){
    switch (choice){
    case CHOICE::WORK:
        return "Work";
    case CHOICE::SKIP_WORK:
        return "Skip work";
    case CHOICE::GO_HOME:
        return "Go home";
    case CHOICE::DEFEND:
        return "Defend";
    case CHOICE::NO_DEFEND:
        return "No defend";
    case CHOICE::GIVE_UP:
        return "Give up";
    default:
        return "None";
    }
}

CHOICE to_choice(int value);

class GlobalVariables{
private:
    struct SaveFile{
        bn::array<char,4> format;
        int8_t end_type;
    };

    SaveFile save;

    CHOICE day_choices[7] = {CHOICE::NONE,CHOICE::NONE,CHOICE::NONE,CHOICE::NONE,CHOICE::NONE,CHOICE::NONE,CHOICE::NONE};
    unsigned int current_day = 0;
    DialogManager dialog_manager;

    /* Especific room and day information */
    bool visited_work_lab_door = false;
    bool visited_work_hall = false;
    bool roof_checked_day_3 = false;
public:
    GlobalVariables();
    ~GlobalVariables() = default;

    DialogManager& getDialogManager();

    /**
     * @param day \in [1-6]
     * @return The choice made in day @param day
     */
    CHOICE dayChoice(unsigned int day);
    /**
     * @param day \in [1-6]
     * @param choice any of class game::CHOICE
     */
    void setDayChoice(unsigned int day,CHOICE choice);

    /**
     * @param day \in [1-6]
     * @return The variant of @param day
     */
    int getDayVariant(int day);

    unsigned int currentDay();
    void goNextDay();    
    #ifdef DEBUG_GAME
    /**
     * @param day \in [0-6]
     * Values above 6 will become 0
     */
    void setDay(int day);
    #endif

    bool hasVisitedLabDoor();
    void setVisitedLabDoor(bool visited);

    bool hasVisitedWorkHall();
    void setVisitedWorkHall(bool visited);

    bool roofCheckedDay3();
    void setRoofCheckedDay3(bool checked);

    bn::optional<int8_t> endType();
    void saveEndType(int8_t end_type);
};
}

#endif