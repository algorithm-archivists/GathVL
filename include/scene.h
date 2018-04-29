#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <cairo.h>
#include "vec.h"
#include "color.h"
#include "shapes.h"

struct layer {
    std::vector<shape*> shapes;

    void draw(cairo_t *ctx);
    void clear();
};

struct scene {
    vec size;
    color bg_clr;
    std::vector<layer> layers;

    scene() : size({600, 400}), bg_clr({0.0, 0.0, 0.0, 1.0}) {
        layers.emplace_back(layer());
    }

    scene(color bg_color) : size({600, 400}), bg_clr(bg_color) {
        layers.emplace_back(layer());
    }

    scene(vec scene_size) : size(scene_size), bg_clr({0.0, 0.0, 0.0, 1.0}) {
        layers.emplace_back(layer());
    }

    scene(vec scene_size, color bg_color) : size(scene_size), bg_clr(bg_color) {
        layers.emplace_back(layer());
    }

    void draw(cairo_t *ctx);
    void add_layer();
    void add_layers(int num_layers);
    void add_layer_at(int position);
    void add_layers_from(int position, int num_layers);
    void clear_layer(int layer_num);
    void clear();
};

#endif //SCENE_H
