#ifndef MULTIANIMATORS_H
#define MULTIANIMATORS_H

#include <vector>
#include "vec.h"

struct vec_multianimator;

struct vec_param {
    vec *a_vec;
    vec start, end;
    int start_frame, end_frame;
};

void vec_update(int frame, vec_multianimator &ma);

struct vec_multianimator {
    std::vector<vec_param> params;
    void (*update)(int frame, vec_multianimator &ma);

    vec_multianimator(std::vector<vec_param> params_vec) :
            params(params_vec), update(vec_update) {}

    vec_multianimator(std::vector<vec_param> params_vec,
                        void(*update0)(int frame, vec_multianimator &ma)) :
            params(params_vec), update(update0) {}
};

#endif //MULTIANIMATORS_H
