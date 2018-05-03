#include "../include/animators.h"

void vec_animator::update(int frame) {
    if (a_vec && frame > start_frame && frame < end_frame) {
        *a_vec = start_vec + (end_vec - start_vec) * (frame - start_frame) /
                    (end_frame - start_frame);
    } else if (a_vec && frame >= end_frame) {
        *a_vec = end_vec;
    }
}
