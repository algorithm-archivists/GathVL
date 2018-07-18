#ifndef GATHVL_SCENE_H
#define GATHVL_SCENE_H

#include <memory>
#include <vector>

#include <cairo.h>

#include "layer.h"
#include "types/color.h"
#include "types/vec.h"

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

    void add_object(std::shared_ptr<object> obj, int layer_pos);

    void add_layer();
    void add_layers(int num_layers);
    void add_layer_at(int position);
    void add_layers_from(int position, int num_layers);

    void clear_layers();
    void clear_layer(int position);

    void clear();

    scene() : scene({600, 400}, {0.0, 0.0, 0.0, 1.0}) { }
    scene(color bg_color) : scene({600, 400}, bg_color) { }
    scene(vec scene_size) : scene(scene_size, {0.0, 0.0, 0.0, 1.0}) {}
    scene(vec scene_size, color bg_color);
};

#endif //GATHVL_SCENE_H
