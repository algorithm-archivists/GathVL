#include "../include/scene.h"
#include <iterator>

void scene::draw(cairo_t *ctx) {
    for (auto l : layers) {
        l.draw(ctx);
    }
}

void scene::update(const int frame) {
    for (auto l : layers) {
        l.update(frame);
    }
}

int scene::add_shape(shape *shp, int layer_pos) {
    layers[layer_pos].shapes.push_back(shp);
    return layers[layer_pos].shapes.size() - 1;
}

int scene::add_animator(animator *anim, int layer_pos, int shape_pos) {
    layers[layer_pos].shapes[shape_pos]->animators.push_back(anim);
    return layers[layer_pos].shapes[shape_pos]->animators.size() - 1;
}

void scene::add_layer() {
    layers.push_back(layer());
}

void scene::add_layers(int num_layers) {
    layers.insert(layers.end(), num_layers, layer());
}

void scene::add_layer_at(int position) {
    auto iter = layers.begin();
    std::advance(iter, position);
    layers.insert(iter, layer());
}

void scene::add_layers_from(int position, int num_layers) {
    auto iter = layers.begin();
    std::advance(iter, position);
    layers.insert(iter, num_layers, layer());
}

void scene::clear_layer(int layer_num) {
    layers[layer_num].clear();
}

void scene::clear() {
    layers.clear();
}
