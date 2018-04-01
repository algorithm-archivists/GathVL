#include "../include/animators.h"

void vec_update(int frame, vec_animator &a) {
    if (a.a_vec && frame > a.start_frame && frame < a.end_frame) {
        *a.a_vec = a.start_vec + (a.end_vec - a.start_vec) *
                    (frame - a.start_frame) / (a.end_frame - a.start_frame);
    } else if (a.a_vec && frame >= a.end_frame) {
        *a.a_vec = a.end_vec;
    }
}
