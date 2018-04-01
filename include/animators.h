#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "vec.h"
#include "color.h"

struct shape;
struct vec_animator;

struct animator {
    int start_frame, end_frame;

    animator(int start, int end) :
                start_frame(start), end_frame(end) {}
};

void vec_update(int frame, vec_animator &a);

struct vec_animator : animator {
    vec *a_vec;
    vec start_vec, end_vec;
    void (*update)(int frame, vec_animator &a);

    vec_animator(int start, int end, vec *avec, vec startvec, vec endvec) :
                animator(start, end), a_vec(avec), start_vec(startvec),
                end_vec(endvec), update(vec_update) {}

    vec_animator(int start, int end, vec *avec, vec startvec, vec endvec,
                    void (*update0)(int frame, vec_animator &a)) :
                animator(start, end), update(update0), a_vec(avec),
                start_vec(startvec), end_vec(endvec) {}
};

#endif //ANIMATIONS_H
