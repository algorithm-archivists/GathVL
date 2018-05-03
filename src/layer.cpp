#include "../include/layer.h"

void layer::draw(cairo_t *ctx) {
    for (auto shp : shapes) {
        shp->draw(ctx);
    }
}

void layer::update(int frame) {
    for (auto shp : shapes) {
        shp->update(frame);
    }
}
