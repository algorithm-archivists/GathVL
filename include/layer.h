#ifndef LAYER_H
#define LAYER_H

#include <cairo.h>
#include <vector>
#include "vec.h"
#include "color.h"
#include "shapes.h"

struct layer {
    std::vector<shape*> shapes;

    void draw(cairo_t *ctx);
    void update(int frame);

    void clear();

    ~layer() {
//        clear();
    }
};

#endif //LAYER_h
