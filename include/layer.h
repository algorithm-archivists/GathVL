#ifndef LAYER_H
#define LAYER_H

#include <memory>
#include <vector>

#include <cairo.h>

#include "vec.h"
#include "color.h"
#include "shapes.h"

struct layer {
    std::vector<std::shared_ptr<shape>> shapes;

    void draw(cairo_t *ctx) const;
    void update(int frame);

    void remove_shape(int position);
    void clear();
};

#endif //LAYER_h
