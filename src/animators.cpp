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
        int index = ptr->size();
        int new_size = ptr->size() + (array.size() - start_point) /
            (end_frame - start_frame);
        while (ptr->size() < new_size) {
            ptr->emplace_back(array[index].x, array[index].y);
            index++;
        }
    }
}
