#ifndef GATHVL_VEC_ANIMATOR_H
#define GATHVL_VEC_ANIMATOR_H

#include "animator.h"
#include "../types/vec.h"

struct vec_animator : animator {
    vec *vec_ptr;
    vec start_vec, end_vec;

    void update(const int frame) override;

    vec_animator(int start, int end, vec *vec_ptr, vec startvec, vec endvec) :
        animator(start, end), vec_ptr(vec_ptr), start_vec(startvec),
        end_vec(endvec) {}
};

#endif //GATHVL_VEC_ANIMATOR_H
