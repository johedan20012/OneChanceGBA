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
        "Boss: Don't worry John, I'm not going to jump.", 
        "Boss: Although I don't suppose it matters now.",
/*30*/  "Boss: Go home and be with your family John.", 
        "Penny: Look at all the plants dying...",
        "Penny: I'm glad you came back last night",
        "Penny: Now go get the paper and come back if youre not going\nto work today.",
        "Penny: Where have you been?",
/*35*/  "Penny: You know what, don't even answer.",
        "Penny: I can't believe you'd do this to me\nat a time like this.",
        "Penny: I'm taking Molly to my mothers.\nGoodbye John.",
        "Boss: John, we need you at the lab.",
        "Boss: We could be on to something, but we understand if\nyou want to be with your family.",
/*40*/  "Annie: Hey you. Glad you could make it.",
        "Annie: You know, since this could be our last day on\nEarth, I've been meaning to ask you something...",
        "Annie: Do you maybe... wanna get out of here?",
        ""
};
}

#endif