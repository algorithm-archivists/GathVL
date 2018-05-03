#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <cairo.h>
#include "vec.h"
#include "color.h"
#include "layer.h"

struct shape;
struct animator;

struct scene {
    vec size;
    color bg_clr;
    std::vector<layer> layers;

    void draw(cairo_t *ctx);
    void update(const int frame);

    int add_shape(shape *shp, int layer_pos);
    int add_animator(animator *anim, int layer_pos, int shape_pos);

    void add_layer();
    void add_layers(int num_layers);
    void add_layer_at(int position);
    void add_layers_from(int position, int num_layers);

    void clear_layer(int layer_num);
    void clear();

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

    ~scene() {
        clear();
    }
};

#endif //SCENE_H
