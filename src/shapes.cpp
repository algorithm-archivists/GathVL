#include "../include/shapes.h"
#include "../include/scene.h"

#include <stdlib.h>
#include <cmath>

static void arc_draw(cairo_t *ctx, shape *shp) {
    cairo_set_source_rgba(ctx, shp->clr.r, shp->clr.g, shp->clr.b, shp->clr.a);
    cairo_rotate(ctx, shp->rotation);

    if (shp->size.x < shp->size.y) {
        cairo_scale(ctx, shp->size.x / shp->size.y, 1.0);
        cairo_arc(ctx, shp->loc.x, shp->loc.y, shp->size.y, shp->ex.a.x,
                    shp->ex.a.y);
        cairo_scale(ctx, shp->size.y / shp->size.x, 1.0);
    } else if (shp->size.x > shp->size.y) {
        cairo_scale(ctx, 1.0, shp->size.y / shp->size.x);
        cairo_arc(ctx, shp->loc.x, shp->loc.y, shp->size.x, shp->ex.a.x,
                    shp->ex.a.y);
        cairo_scale(ctx, 1.0, shp->size.x / shp->size.y);
    } else if (shp->size.x == shp->size.y && shp->size.x != 0) {
        cairo_arc(ctx, shp->loc.x, shp->loc.y, shp->size.x, shp->ex.a.x,
                    shp->ex.a.y);
    }

    if (shp->fill)
        cairo_fill(ctx);

    cairo_stroke(ctx);
    cairo_rotate(ctx, -1.0 * shp->rotation);
}

shape ellipse(color ellipse_clr, vec location, vec size, double rotation,
                bool fill) {
    shape shp;

    shp.type = ELLIPSE;
    shp.clr = ellipse_clr;
    shp.loc = location;
    shp.size = {abs(size.x), abs(size.y)};
    shp.ex.a = {0.0, 2.0 * M_PI};
    shp.rotation = rotation;
    shp.fill = fill;
    shp.draw = arc_draw;

    return shp;
}

shape arc(color arc_clr, vec location, vec size, vec angles) {
    shape shp;

    shp.type = ARC;
    shp.clr = arc_clr;
    shp.loc = location;
    shp.size = size;
    shp.ex.a = angles;
    shp.fill = false;
    shp.draw = arc_draw;

    return shp;
}

static void line_draw(cairo_t * ctx, shape *s) {
    cairo_set_source_rgba(ctx, s->clr.r, s->clr.g, s->clr.b, s->clr.a);
    cairo_move_to(ctx, s->loc.x, s->loc.y);
    cairo_line_to(ctx, s->ex.a.x, s->ex.a.y);
    cairo_stroke(ctx);
}

shape line(color line_clr, vec start, vec end) {
    shape shp;

    shp.type = LINE;
    shp.clr = line_clr;
    shp.loc = start;
    shp.ex.a = end;
    shp.draw = line_draw;

    return shp;
}

static void rectangle_draw(cairo_t *ctx, shape *shp) {
    cairo_set_source_rgba(ctx, shp->clr.r, shp->clr.g, shp->clr.b, shp->clr.a);
    cairo_rotate(ctx, shp->rotation);

    cairo_rectangle(ctx, shp->loc.x, shp->loc.y, shp->size.x, shp->size.y);

    if (shp->fill)
        cairo_fill(ctx);

    cairo_stroke(ctx);
    cairo_rotate(ctx, -1.0 * shp->rotation);
}

shape rectangle(color rectangle_clr, vec location, vec size, double rotation,
                    bool fill) {
    shape shp;

    shp.type = RECTANGLE;
    shp.clr = rectangle_clr;
    shp.loc = location;
    shp.size = size;
    shp.rotation = rotation;
    shp.fill = fill;
    shp.draw = rectangle_draw;

    return shp;
}
