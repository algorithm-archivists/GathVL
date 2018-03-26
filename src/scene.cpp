#include "../include/scene.h"

void scene::scene_init() {
    scene_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, size.x,
                                                size.y);
    scene_ctx = cairo_create(scene_surface);
    cairo_set_line_width(scene_ctx, 3);
    cairo_set_font_size(scene_ctx, 50.0);
    cairo_set_line_join(scene_ctx, CAIRO_LINE_JOIN_BEVEL);
    cairo_set_line_cap(scene_ctx, CAIRO_LINE_CAP_ROUND);

    cairo_set_source_rgba(scene_ctx, bg_clr.r, bg_clr.g, bg_clr.b, bg_clr.a);
    cairo_rectangle(scene_ctx, 0, 0, size.x, size.y);
    cairo_fill(scene_ctx);
}

void scene::clear() {
    cairo_set_source_rgba(scene_ctx, bg_clr.r, bg_clr.g, bg_clr.b, bg_clr.a);
    cairo_set_operator(scene_ctx, CAIRO_OPERATOR_SOURCE);
    cairo_paint(scene_ctx);
}

void scene::destroy(){
    cairo_destroy(scene_ctx);
    cairo_surface_destroy(scene_surface);
}
