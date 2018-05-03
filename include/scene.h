#ifndef SCENE_H
#define SCENE_H

#include <memory>
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

    std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> surface;
    std::unique_ptr<cairo_t, decltype(&cairo_destroy)> context;

    void draw();
    void update(int frame);

    void add_shape(std::shared_ptr<shape> shp, int layer_pos);

    void add_layer();
    void add_layers(int num_layers);
    void add_layer_at(int position);
    void add_layers_from(int position, int num_layers);

    scene() : scene({600, 400}, {0.0, 0.0, 0.0, 1.0}) { }
    scene(color bg_color) : scene({600, 400}, bg_color) { }
    scene(vec scene_size) : scene(scene_size, {0.0, 0.0, 0.0, 1.0}) {}
    scene(vec scene_size, color bg_color);
};

#endif //SCENE_H
