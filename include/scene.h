#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <cairo.h>
#include "vec.h"
#include "color.h"
#include "shapes.h"

struct scene {
    vec size;
    color bg_clr;
    std::vector<shape*> shape_vector;

    scene() :
            size({600, 400}), bg_clr({0.0, 0.0, 0.0, 1.0}) {}

    scene(color bg_color) :
            size({600, 400}), bg_clr(bg_color) {}

    scene(vec scene_size) :
            size(scene_size), bg_clr({0.0, 0.0, 0.0, 1.0}) {}

    scene(vec scene_size, color bg_color) :
            size(scene_size), bg_clr(bg_color) {}

    void draw(cairo_t *ctx);

};

#endif //SCENE_H
