#include "../include/animations.h"
#include "../include/shapes.h"

void vec_animator::vec_update(int frame) {
    if (a && frame > start_frame && frame < end_frame) {
        *a = start_vec + (end_vec - start_vec) * (frame - start_frame) /
                (end_frame - start_frame);
    } else if (a && frame >= end_frame) {
        *a = end_vec;
    }
}
