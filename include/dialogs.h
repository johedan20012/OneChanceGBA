#ifndef DIALOGS_H
#define DIALOGS_H
#define MAX_DIALOGS 50

#include "bn_string_view.h"

namespace game{
inline constexpr bn::string_view DIALOGS[MAX_DIALOGS] = {
/*0 */  "Penny: Hurry up, honey! You'll be late for work.",
        "Penny: Today is a big day! Get a move on!",
        "Molly: Do I really have to go to school today, Daddy?",
        "Jim: Well if it isn't the fucking saviour.",
        "Boss: Congratulations John. This is a big step.",
/*5 */  "Annie: We should go out for a drink to celebrate, John.",
        "Ryan: Good work Doc'. You're gonna be huge.",
        "Construction guy: Sorry bro. No entry today.",
        "Molly: Mum's in the bath",
        "Penny: The phone's been ringing all morning for you",
/*10*/  "Penny: Must be important",
        "Boss: We're fucked John. The drug is dangerous!",
        "Boss: We're going to get our funding pulled.",
        "Ryan: It's not really as dangerous as they say it is...",
        "Ryan: ...is it Doc'?",
/*15*/  "It's Locked.",
        "Matthew: ...Oh God...",
        "Matthew: ...John, what have we done?",
        "Matthew: I've done the tests a thousand times",
        "Matthew: It's so much worse than we thought",
/*20*/  "Matthew: It's going to change everything...",
        "Penny: Do you really have to go in today?",
        "Penny: Does anything really matter any more?",
        "Molly: Why don't I have to go to school today?",
        "Bruce: There must be something we can do.",
/*25*/  "Ryan: What's happened here?! Where is everyone?",
        "Ryan: You're going home Doc'?",
        "Ryan: I've got the keys to the lab here if you want to work?",
        ""     
};
}

#endif