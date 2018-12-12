#include "../../include/animators/color_animator.h"

void color_animator::update(const int frame) {
    if (color_ptr && frame >= start_frame && frame < end_frame) {
        *color_ptr = start_color + (end_color - start_color) *
            (frame - start_frame) / (end_frame - start_frame);
    }
}
