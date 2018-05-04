#include "../include/scene.h"
#include <iterator>

scene::scene(vec scene_size, color bg_color)
    : size(scene_size), bg_clr(bg_color),
      surface(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, static_cast<int>(size.x), static_cast<int>(size.y)), cairo_surface_destroy),
      context(cairo_create(surface.get()), cairo_destroy) {

    layers.emplace_back();
    cairo_set_line_width(context.get(), 3);
    cairo_set_font_size(context.get(), 50.0);
    cairo_set_line_join(context.get(), CAIRO_LINE_JOIN_BEVEL);
    cairo_set_line_cap(context.get(), CAIRO_LINE_CAP_ROUND);
}

void scene::draw() {
    cairo_set_source_rgba(context.get(), bg_clr.r, bg_clr.g, bg_clr.b, bg_clr.a);
    cairo_set_operator(context.get(), CAIRO_OPERATOR_SOURCE);
    cairo_paint(context.get());

    for (const auto& l : layers) {
        l.draw(context.get());
    }
}

void scene::update(const int frame) {
    for (auto& l : layers) {
        l.update(frame);
    }
}

void scene::add_shape(std::shared_ptr<shape> shp, int layer_pos) {
    layers[layer_pos].shapes.push_back(shp);
}

void scene::add_layer() {
    layers.emplace_back();
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
