#include "../include/animators.h"

#include <iostream>

void vec_animator::update(const int frame) {
    if (vec_ptr && frame > start_frame && frame < end_frame) {
        *vec_ptr = start_vec + (end_vec - start_vec) * (frame - start_frame) /
                   (end_frame - start_frame);
    } else if (vec_ptr && frame >= end_frame) {
        *vec_ptr = end_vec;
    } else {
        *vec_ptr = start_vec;
    }
}

void vec_array_animator::update(const int frame) {
    if (!array.empty() && frame >= start_frame && frame < end_frame) {
        int count = (frame - start_frame) / (end_frame - start_frame);
        std::cout << ptr->size() << std::endl;
        for (; start_point <= start_point + count; ++start_point) {
            ptr->emplace_back(array[start_point].x, array[start_point].y);
        }
    }
}
