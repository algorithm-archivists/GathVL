#include "../../include/objects/arc.h"

void arc::draw(cairo_t *ctx) const {
    cairo_save(ctx);
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);

    if (size.x < size.y && (size.x != 0 || size.y != 0)) {
        cairo_scale(ctx, size.x / size.y, 1.0);
        cairo_arc(ctx, location.x, location.y, size.y, angles.x, angles.y);
    } else if (size.x > size.y && (size.x != 0 || size.y != 0)) {
        cairo_scale(ctx, 1.0, size.y / size.x);
        cairo_arc(ctx, location.x, location.y, size.x, angles.x, angles.y);
    } else if (size.x == size.y && size.x != 0) {
        cairo_arc(ctx, location.x, location.y, size.x, angles.x, angles.y);
    }

    cairo_stroke(ctx);
    cairo_restore(ctx);
}
