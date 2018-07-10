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

template <typename T>
struct vector_animator : animator {
    std::vector<T> data;
    std::vector<T> *vector_ptr;
    int start_point;

    void update(const int frame) override {
        if (!data.empty() && frame >= start_frame && frame < end_frame) {
            int index = vector_ptr->size();
            int new_size = vector_ptr->size() + (data.size() - start_point) /
                (end_frame - start_frame);

            while (vector_ptr->size() < new_size && vector_ptr) {
                vector_ptr->push_back(data[index]);
                index++;
            }
        }
    }

    vector_animator(int start_frame, int end_frame, int start_point,
                    const std::vector<T>& data, std::vector<T> *vector_ptr) :
        animator(start_frame, end_frame), data(data), vector_ptr(vector_ptr),
        start_point(start_point) {}
};

#endif //ANIMATIONS_H
