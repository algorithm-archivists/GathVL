#include "../include/shapes.h"
#include "../include/scene.h"

#include <stdlib.h>
#include <cmath>

static void ellipse_draw(cairo_t *ctx, shape &shp) {
    cairo_set_source_rgba(ctx, shp.clr.r, shp.clr.g, shp.clr.b, shp.clr.a);
    cairo_rotate(ctx, shp.rotation);

    if (shp.size.x < shp.size.y) {
        cairo_scale(ctx, shp.size.x / shp.size.y, 1.0);
        cairo_arc(ctx, shp.loc.x, shp.loc.y, shp.size.y, 0, 2 * M_PI);
    } else if (shp.size.x > shp.size.y) {
        cairo_scale(ctx, 1.0, shp.size.y / shp.size.x);
        cairo_arc(ctx, shp.loc.x, shp.loc.y, shp.size.x, 0, 2 * M_PI);
    } else if (shp.size.x == shp.size.y && shp.size.x != 0) {
        cairo_arc(ctx, shp.loc.x, shp.loc.y, shp.size.x, 0, 2 * M_PI);
    }

    cairo_stroke(ctx);
    cairo_rotate(ctx, -1.0 * shp.rotation);
}

shape ellipse(color ellipse_clr, vec location, vec size, double rotation) {
    shape shp;

    shp.type = ELLIPSE;
    shp.clr = ellipse_clr;
    shp.loc = location;
    shp.size = {abs(size.x), abs(size.y)};
    shp.rotation = rotation;
    shp.draw = ellipse_draw;

    return shp;
}

static void arc_draw(cairo_t *ctx, shape &shp) {
    cairo_set_source_rgba(ctx, shp.clr.r, shp.clr.g, shp.clr.b, shp.clr.a);
    cairo_rotate(ctx, shp.rotation);

    if (shp.size.x < shp.size.y) {
        cairo_scale(ctx, shp.size.x / shp.size.y, 1.0);
        cairo_arc(ctx, shp.loc.x, shp.loc.y, shp.size.y, shp.ex.a.x,
                    shp.ex.a.y);
        cairo_scale(ctx, shp.size.y / shp.size.x, 1.0);
    } else if (shp.size.x > shp.size.y) {
        cairo_scale(ctx, 1.0, shp.size.y / shp.size.x);
        cairo_arc(ctx, shp.loc.x, shp.loc.y, shp.size.x, shp.ex.a.x,
                    shp.ex.a.y);
        cairo_scale(ctx, 1.0, shp.size.x / shp.size.y);
        cairo_arc(ctx, shp.loc.x, shp.loc.y, shp.size.y, 0, 2 * M_PI);
    } else if (shp.size.x == shp.size.y && shp.size.x != 0) {
        cairo_arc(ctx, shp.loc.x, shp.loc.y, shp.size.x, shp.ex.a.x,
                    shp.ex.a.y);
    }

    cairo_stroke(ctx);
    cairo_rotate(ctx, -1.0 * shp.rotation);
}

shape arc(color arc_clr, vec location, vec size, vec angles, double rotation) {
    shape shp;

    shp.type = ARC;
    shp.clr = arc_clr;
    shp.loc = location;
    shp.size = size;
    shp.ex.a = angles;
    shp.rotation = rotation;
    shp.draw = arc_draw;

    return shp;
}
