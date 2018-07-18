#include "../include/layer.h"

void layer::draw(cairo_t *ctx) const {
    for (const auto& obj : objects) {
        obj->draw(ctx);
    }
}

void layer::update(int frame) {
    for (auto& obj : objects) {
        obj->update(frame);
    }
}

void layer::remove_object(int position) {
    auto iter = objects.begin();
    std::advance(iter, position);
    objects.erase(iter);
}

void layer::clear() {
    objects.clear();
}
