#ifndef DIALOGS_H
#define DIALOGS_H
#define MAX_DIALOGS 10

#include "bn_string_view.h"

namespace game{
inline constexpr bn::string_view DIALOGS[MAX_DIALOGS] = {
    "Penny: Hurry up, honey! You'll be late for work.",
    "Penny: Today is a big day! Get a move on!",
    "Molly: Do I really have to go to school today, Daddy?",
    ""
};
}

#endif