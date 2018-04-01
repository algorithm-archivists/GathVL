#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <vector>
#include "vec.h"
#include "color.h"

struct shape;

struct animator {
    int start_frame, end_frame;
    void (*update)(int frame);

    animator(int start, int end, void (*update0)(int frame)) :
                start_frame(start), end_frame(end), update(update0){}
};

struct vec_animator : animator {
    vec *a;
    vec start_vec, end_vec;

    void vec_update(int frame);

    vec_animator(int start, int end, vec *a0, vec start_vec0, vec end_vec0) :
                animator(start, end, &vec_update), a(a0), start_vec(start_vec0),
                end_vec(end_vec0) {}

    vec_animator(int start, int end, void (*update0)(int frame), vec *a0,
                    vec start_vec0, vec end_vec0) :
                animator(start, end, update0), a(a0), start_vec(start_vec0),
                end_vec(end_vec0) {}
};

#endif //ANIMATIONS_H
