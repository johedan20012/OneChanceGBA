#ifndef DIALOGS_H
#define DIALOGS_H
#define MAX_DIALOGS 30

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
        ""      
};
}

#endif