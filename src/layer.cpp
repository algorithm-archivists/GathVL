#include "../include/layer.h"

void layer::draw(cairo_t *ctx) const {
    for (const auto& shp : shapes) {
        shp->draw(ctx);
    }
}

void layer::update(int frame) {
    for (auto& shp : shapes) {
        shp->update(frame);
    }
}

void layer::remove_shape(int position) {
    auto iter = shapes.begin();
    std::advance(iter, position);
    shapes.erase(iter);
}

void layer::clear() {
    shapes.clear();
}
