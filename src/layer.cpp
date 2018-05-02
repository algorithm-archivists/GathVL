#include "../include/layer.h"

void layer::draw(cairo_t *ctx) {
    for (auto shp : shapes) {
        shp->draw(ctx);
    }
}

void layer::clear() {
    while (shapes.size() > 0) {
        auto shp = shapes.back();
        shapes.pop_back();
        delete shp;
    }
}
