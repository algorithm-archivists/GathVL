#include "../include/shapes.h"
#include "../include/scene.h"

#include <stdlib.h>

static void ellipse_handler(cairo_t *ctx, shape &shp) {
    cairo_set_source_rgba(ctx, shp.clr.r, shp.clr.g, shp.clr.b, shp.clr.a);
    cairo_rotate(ctx, shp.angle);

    if (shp.size.x < shp.size.y) {
        cairo_scale(ctx, shp.size.x / shp.size.y, 1.0);
        cairo_arc(ctx, shp.location.x, shp.location.y, shp.size.y, 0, 2 * M_PI);
    } else if (shp.size.x > shp.size.y) {
        cairo_scale(ctx, 1.0, shp.size.y / shp.size.x);
        cairo_arc(ctx, shp.location.x, shp.location.y, shp.size.x, 0, 2 * M_PI);
    } else if (shp.size.x == shp.size.y && shp.size.x != 0) {
        cairo_arc(ctx, shp.location.x, shp.location.y, shp.size.x, 0, 2 * M_PI);
    }

    cairo_stroke(ctx);
    cairo_rotate(ctx, -1.0 * shp.angle);
}

void ellipse(shape &shp, color ellipse_clr, vec location, vec size,
                double angle) {
    shp.type = ELLIPSE;
    shp.clr = ellipse_clr;
    shp.location = location;
    shp.size = {abs(size.x), abs(size.y)};
    shp.angle = angle;
    shp.handler = ellipse_handler;
}

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
