#ifndef SNOWDATA_H
#define SNOWDATA_H

#include "snowParticles.h"

namespace game{
inline constexpr FadeInOutArea ROOF_IN_AREAS[5] = {
    {bn::fixed_rect(8.0, -80, 256.0, 30.0),0,7680},
    {bn::fixed_rect(-1.5, -65.0, 149.0, 30.0),0,4470},
    {bn::fixed_rect(103.0, -33.0, 28.0, 16.0),1,448},
    {bn::fixed_rect(-31.5, -18.0, 19.0, 46.0),2,874},
    {bn::fixed_rect(48.5, -17.0, 17.0, 44.0),2,748}
};

inline constexpr FadeInOutArea ROOF_OUT_AREAS[5] = {
    {bn::fixed_rect(-27.0, 53.0, 132.0, 54.0),3,0},
    {bn::fixed_rect(124.0, 53.0, 24.0, 54.0),4,0},
    {bn::fixed_rect(90.0, 72.0, 30.0, 16.0),5,0},
    {bn::fixed_rect(52.0, 38.5, 18.0, 25.0),3,0},
    {bn::fixed_rect(-2.0, 18.0, 182.0, 6.0),6,0}
};

}
#endif