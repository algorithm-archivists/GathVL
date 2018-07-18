#include "../../include/objects/ellipse.h"

void ellipse::draw(cairo_t *ctx) const {
    cairo_save(ctx);
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_translate(ctx, location.x, location.y);
    cairo_rotate(ctx, rotation);

    if (size.x < size.y && (size.x != 0 || size.y != 0)) {
        cairo_scale(ctx, size.x / size.y, 1.0);
        cairo_arc(ctx, 0.0, 0.0, size.y, angles.x, angles.y);
    } else if (size.x > size.y && (size.x != 0 || size.y != 0)) {
        cairo_scale(ctx, 1.0, size.y / size.x);
        cairo_arc(ctx, 0.0, 0.0, size.x, angles.x, angles.y);
    } else if (size.x == size.y && size.x != 0) {
        cairo_arc(ctx, 0.0, 0.0, size.x, angles.x, angles.y);
    }

    if (fill) {
        cairo_fill(ctx);
    }

    cairo_stroke(ctx);
    cairo_restore(ctx);
}
