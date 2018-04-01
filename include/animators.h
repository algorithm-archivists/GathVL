#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "vec.h"
#include "color.h"

struct vec_animator;

void vec_update(int frame, vec_animator &a);

struct vec_animator {
    vec *a_vec;
    vec start_vec, end_vec;
    int start_frame, end_frame;
    void (*update)(int frame, vec_animator &a);

    vec_animator(int start, int end, vec *avec, vec startvec, vec endvec) :
                start_frame(start), end_frame(end), a_vec(avec),
                start_vec(startvec), end_vec(endvec), update(vec_update) {}

    vec_animator(int start, int end, vec *avec, vec startvec, vec endvec,
                    void (*update0)(int frame, vec_animator &a)) :
                start_frame(start), end_frame(end), update(update0),
                a_vec(avec), start_vec(startvec), end_vec(endvec) {}
};

#endif //ANIMATIONS_H
