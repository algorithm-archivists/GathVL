#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <vector>

#include "vec.h"
#include "color.h"

struct animator {
    int start_frame, end_frame;

    virtual void update(const int frame) = 0;

    animator(int start, int end) : start_frame(start), end_frame(end) {}
    virtual ~animator() {}
};

struct vec_animator : animator {
    vec *vec_ptr;
    vec start_vec, end_vec;

    void update(const int frame) override;

    vec_animator(int start, int end, vec *a, vec startvec, vec endvec) :
        animator(start, end), vec_ptr(a), start_vec(startvec),
        end_vec(endvec) {}
};

struct vec_array_animator : animator {
    std::vector<vec> array;
    std::vector<vec> *ptr;
    int start_point;

    void update(const int frame) override;

    vec_array_animator(int start_frame, int end_frame, int start_point,
                       const std::vector<vec>& array, std::vector<vec> *ptr) :
        animator(start_frame, end_frame), array(array), ptr(ptr),
        start_point(start_point) {}
};

#endif //ANIMATIONS_H
