#include "../include/animators.h"

void vec_animator::update(const int frame) {
    if (vec_ptr && frame > start_frame && frame < end_frame) {
        *vec_ptr = start_vec + (end_vec - start_vec) * (frame - start_frame) /
                   (end_frame - start_frame);
    } else if (vec_ptr && frame >= end_frame) {
        *vec_ptr = end_vec;
    }
}
