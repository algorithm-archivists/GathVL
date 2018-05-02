#include "../include/layer.h"

void layer::draw(cairo_t *ctx) {
    for (auto shp : shapes) {
        shp->draw(ctx);
    }
}

void layer::clear() {
    shapes.clear();
}
