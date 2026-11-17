#ifndef SNOWPARTICLES_H
#define SNOWPARTICLES_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_palette_ptr.h"
#include "bn_sprite_affine_mat_ptr.h"

#include "bn_span.h"
#include "bn_vector.h"
#include "bn_optional.h"
#include "bn_fixed_rect.h"

#include "player.h"
#include "globalVariables.h"

namespace game{

struct FadeInOutArea{
    bn::fixed_rect area;
    int palette_indx;
    int weight;
};

class Particle{
private:
    static constexpr int FADE_OUT_COLOR_INDX[7] = {1,7,13,19,25,31,37};
    static constexpr int FADE_STEPS = 5;
    static constexpr int FADE_STEP_TIME = 2;
    static constexpr bn::fixed PARTICLE_SPEED_Y = {0.375}; // old 0.575
    static constexpr bn::fixed PARTICLE_SPEED_X = {0.25}; //0.25 cannon
    
    const bn::span<const FadeInOutArea> fade_out_areas;

    bn::sprite_tiles_ptr tiles;
    bn::sprite_ptr spr;
    const bn::fixed_point init_pos;
    const int fade_in_color; 
    int fade_out_color;
    int curr_color;
    int frames_to_step_fade;
    bool fading_in;
    bool fading_out;
    bool faded_out;
    bn::fixed min_x;
    bn::fixed max_x;
    bool going_right = false;
    const bn::fixed fade_out_y;

    void update_particle_color();
public:
    Particle(bool _go_right,bn::fixed_point _init_pos,bn::fixed _fade_out_y,bn::fixed _min_x,bn::fixed _max_x,bn::sprite_affine_mat_ptr scale,int _fade_in_color,bn::sprite_palette_ptr palette,bn::span<const FadeInOutArea> _fade_out_areas);
    ~Particle() = default;

    void update(bn::optional<bn::fixed_rect> area_to_avoid);
};

class SnowParticles{
private:
    static constexpr int FADE_IN_COLOR_INDX[7] = {6,12,18,24,30,36,42};
    static constexpr bn::fixed MAX_X_L = {36};
    static constexpr bn::fixed MIN_X_L = {3};

    GlobalVariables &global_var;
    Player& player;

    const bn::span<const FadeInOutArea> fade_in_areas;
    int TOTAL_WEIGHT_FADE_IN = 0;
    const bn::span<const FadeInOutArea> fade_out_areas;
    bool avoid_player;

    bn::sprite_palette_ptr snow_palette;
    bn::vector<Particle,51> particles;

    void create_particles(int n,bn::sprite_affine_mat_ptr scale);

public:
    SnowParticles(GlobalVariables &_global_var,Player &_player,bn::span<const FadeInOutArea> in_areas,bn::span<const FadeInOutArea> out_areas,bn::sprite_palette_item _snow_palette,bool _avoid_player = false);
    ~SnowParticles() = default;

    void update();
};
}
#endif