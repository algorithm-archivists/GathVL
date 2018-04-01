#include "../include/multianimators.h"

void vec_update(int frame, vec_multianimator &ma) {
    for (auto p : ma.params) {
        if (p.a_vec && frame > p.start_frame && frame < p.end_frame) {
            *p.a_vec = p.start + (p.end - p.start) * (frame - p.start_frame) /
                        (p.end_frame - p.start_frame);
        } else if (p.a_vec && frame >= p.end_frame) {
            *p.a_vec = p.end;
        }
    }
}
