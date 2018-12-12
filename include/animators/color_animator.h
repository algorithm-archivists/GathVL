#ifndef GATHVL_COLOR_ANIMATOR_H
#define GATHVL_COLOR_ANIMATOR_H

#include "animator.h"
#include "../types/color.h"

struct color_animator : animator {
    color *color_ptr;
    color start_color, end_color;

    void update(const int frame) override;

    color_animator(int start, int end, color *color_ptr, color startclr,
                   color endclr) :
        animator(start, end), color_ptr(color_ptr), start_color(startclr),
        end_color(endclr) {}
};

#endif //GATHVL_VEC_ANIMATOR_H
