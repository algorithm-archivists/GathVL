#ifndef LAYER_H
#define LAYER_H

#include <cairo.h>
#include <vector>
#include <memory>
#include "vec.h"
#include "color.h"
#include "shapes.h"

struct layer {
    std::vector<std::unique_ptr<shape>> shapes;

    layer() {}

    layer(std::vector<std::unique_ptr<shape>> shapes0) : shapes(shapes0) {}

    void draw(cairo_t *ctx);
    void clear();
};

#endif //LAYER_h
