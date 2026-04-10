#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

#include "bn_regular_bg_ptr.h"

#include "bn_vector.h"
#include "bn_optional.h"
#include "bn_unique_ptr.h"

#include "pair.h"
#include "timer.h"

namespace game{
class DialogManager{
private:
    bn::optional<bn::regular_bg_ptr> bottom_text_bg;
    bool bg_active = false;

    bn::vector<bn::sprite_ptr,30> bottom_text;
    bn::vector<Pair<int,int>,10> act_dialog_sequence;
    int dialog_sequence_indx;
    bn::unique_ptr<Timer> bottom_text_timer;
    int bottom_text_duration;
    bn::sprite_text_generator bottom_text_gen;

    void nextDialog();
public:
    DialogManager();
    ~DialogManager() = default;

    void setBg(bn::regular_bg_ptr _bg);
    void resetBg();

    void setBottomText(int dialog_index,int duration = -1);
    void setBottomTextDuration(int duration);
    void setActDialogSequence(const bn::vector<Pair<int,int>,10>& _dialog);
    void resetBottomText();

    bool hasADialogSequence();

    void update();
};
}

#endif