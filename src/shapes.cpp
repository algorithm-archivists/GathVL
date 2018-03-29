#include "../include/shapes.h"
#include "../include/scene.h"

void create_circle(scene &s, double radius, vec location, color clr) {
    cairo_set_source_rgba(s.scene_ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_arc(s.scene_ctx, location.x, location.y, radius, 0, 2 * M_PI);
    cairo_stroke(s.scene_ctx);
}

void create_rectangle(scene &s, vec size, vec location, color clr) {
    cairo_set_source_rgba(s.scene_ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_rectangle(s.scene_ctx, location.x, location.y, size.x, size.y);
    cairo_stroke(s.scene_ctx);
}
