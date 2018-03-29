#include "../include/shapes.h"
#include "../include/scene.h"

#include <stdlib.h>

static void ellipse_draw(cairo_t *ctx, shape &shp) {
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

shape ellipse(color ellipse_clr, vec location, vec size, double rotation) {
    shape shp;

    shp.type = ELLIPSE;
    shp.clr = ellipse_clr;
    shp.location = location;
    shp.size = {abs(size.x), abs(size.y)};
    shp.rotation = rotation;
    shp.draw = ellipse_draw;

    return shp;
}



shape arc(color arc_clr, vec location, vec size, double start_angle,
            double end_angle, double rotation) {
    shape shp;

    shp.type = ARC;
    shp.clr = ellipse_clr;
    shp.location = location;
    shp.size = {abs(size.x), abs(size.y)};
    shp.rotation = rotation;
    shp.extra = {start_angle, end_angle};
    shp.draw = arc_draw;

    return shp;
}
