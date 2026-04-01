#include "dialogManager.h"

#include "dialogs.h"
#include "bn_assert.h"

namespace game{
DialogManager::DialogManager():
    bottom_text_gen(JostFontVar8x16Mini){

    bottom_text_gen.set_center_alignment();
    bottom_text_gen.set_bg_priority(1);
    bottom_text_gen.set_z_order(2);
}

void DialogManager::setBg(bn::regular_bg_ptr _bg){
    bottom_text_bg = _bg;
    bottom_text_bg->set_priority(1);
    bottom_text_bg->set_blending_enabled(true);
    bottom_text_bg->set_blending_top_enabled(true);
    bottom_text_bg->set_visible(false);
}

void DialogManager::resetBg(){
    if(bottom_text_bg) bottom_text_bg.reset();
}

void DialogManager::setBottomText(int dialog_index,int duration){
    BN_ASSERT(0<= dialog_index && dialog_index < MAX_DIALOGS," ");
    if(duration >= 0) setBottomTextDuration(duration);

    bottom_text.clear();
    bottom_text_gen.generate(bn::fixed_point(0,70),DIALOGS[dialog_index],bottom_text);
    if(bottom_text_bg) bottom_text_bg->set_visible(true);
}

void DialogManager::setBottomTextDuration(int duration){
    if(duration < 0){
        bottom_text_timer.reset();
        return;
    }

    if(bottom_text_timer) bottom_text_timer.reset();
    bottom_text_timer = bn::make_unique<Timer>();

    bottom_text_duration = duration;
}

void DialogManager::nextDialog(){
    if(dialog_sequence_indx >= act_dialog_sequence.size()){
        resetBottomText();
        return;
    }

    setBottomText(act_dialog_sequence[dialog_sequence_indx].first,act_dialog_sequence[dialog_sequence_indx].second);
    dialog_sequence_indx++;
}

void DialogManager::setActDialogSequence(const bn::vector<Pair<int,int>,10>& _dialog){
    act_dialog_sequence = _dialog;
    dialog_sequence_indx = 0;
    nextDialog();
}

void DialogManager::resetBottomText(){
    bottom_text.clear();
    bottom_text_timer.reset();
    act_dialog_sequence.clear();
    if(bottom_text_bg) bottom_text_bg->set_visible(false);
}

void DialogManager::update(){
    if(bottom_text_timer && bottom_text_timer->elapsedFrames() > bottom_text_duration)
        nextDialog();
}
}