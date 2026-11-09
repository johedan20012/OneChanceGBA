#ifndef SNOWPARTICLES_H
#define SNOWPARTICLES_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_palette_ptr.h"
#include "bn_sprite_affine_mat_ptr.h"

#include "bn_vector.h"
#include "bn_fixed_rect.h"

#include "globalVariables.h"

namespace game{

class SnowParticles{
private:
    static constexpr int FADE_IN_COLOR_INDX[7] = {6,12,18,24,30,36,42};
    static constexpr int FADE_OUT_COLOR_INDX[7] = {1,7,13,19,25,31,37};
    static constexpr int FADE_STEPS = 5;
    static constexpr int FADE_STEP_TIME = 2;
    static constexpr bn::fixed PARTICLE_SPEED_Y = {0.375}; // old 0.575
    static constexpr bn::fixed PARTICLE_SPEED_X = {0.25}; //0.25 cannon
    static constexpr bn::fixed MAX_X_L = {36};
    static constexpr bn::fixed MIN_X_L = {3};
    
    struct FadeInOutArea{
        bn::fixed_rect area;
        int palette_indx;
        int weight;
    };

    static constexpr int MAX_FADE_IN_AREAS = 5;
    static constexpr FadeInOutArea fade_in_areas[MAX_FADE_IN_AREAS] = {
        {bn::fixed_rect(8.0, -80, 256.0, 30.0),0,7680},
        {bn::fixed_rect(-1.5, -65.0, 149.0, 30.0),0,4470},
        {bn::fixed_rect(103.0, -33.0, 28.0, 16.0),1,448},
        {bn::fixed_rect(-31.5, -18.0, 19.0, 46.0),2,874},
        {bn::fixed_rect(48.5, -17.0, 17.0, 44.0),2,748}
    };
    static constexpr int TOTAL_WEIGHT_FADE_IN = 14220;

    static constexpr int MAX_FADE_OUT_AREAS = 5;
    static constexpr FadeInOutArea fade_out_areas[MAX_FADE_OUT_AREAS] = {
        {bn::fixed_rect(-27.0, 53.0, 132.0, 54.0),3,0},
        {bn::fixed_rect(124.0, 53.0, 24.0, 54.0),4,0},
        {bn::fixed_rect(90.0, 72.0, 30.0, 16.0),5,0},
        {bn::fixed_rect(52.0, 38.5, 18.0, 25.0),3,0},
        {bn::fixed_rect(-2.0, 18.0, 182.0, 6.0),6,0}
    };

    class Particle{
    private:
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
        Particle(bool _go_right,bn::fixed_point _init_pos,bn::fixed _fade_out_y,bn::fixed _min_x,bn::fixed _max_x,bn::sprite_affine_mat_ptr scale,int _fade_in_color,bn::sprite_palette_ptr palette);
        ~Particle() = default;

        void update();
    };
    GlobalVariables &global_var;

    bn::sprite_palette_ptr snow_palette;

    bn::vector<Particle,51> particles;

    void create_particles(int n,bn::sprite_affine_mat_ptr scale);

public:
    SnowParticles(GlobalVariables &_global_var);
    ~SnowParticles() = default;

    void update();
};
}
#endif