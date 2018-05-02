#ifndef LAYER_H
#define LAYER_H

#include <cairo.h>
#include <vector>
#include "vec.h"
#include "color.h"
#include "shapes.h"

struct layer {
    std::vector<shape*> shapes;

    layer() {}

    void draw(cairo_t *ctx);
    void clear();
};

#endif //LAYER_h
