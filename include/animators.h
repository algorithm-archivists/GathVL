#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "vec.h"
#include "color.h"

enum animator_type {
    VEC
};

struct animator {
    int start_frame, end_frame;

    virtual void update(int frame) = 0;

    animator(int start, int end) : start_frame(start), end_frame(end) {}
};

struct vec_animator : animator {
    vec *a_vec;
    vec start_vec, end_vec;

    void update(int frame);

    vec_animator(int start, int end, vec *avec, vec startvec, vec endvec) :
            animator(start, end), a_vec(avec), start_vec(startvec),
            end_vec(endvec) {}
};

#endif //ANIMATIONS_H
