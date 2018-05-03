#ifndef ANIMATIONS_H
#define ANIMATIONS_H

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

    vec_animator(int start, int end, vec *a, vec startvec, vec endvec)
        : animator(start, end), vec_ptr(a),
          start_vec(startvec), end_vec(endvec) {}
};

#endif //ANIMATIONS_H
