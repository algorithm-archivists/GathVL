#include "../../include/objects/rectangle.h"

void rectangle::draw(cairo_t *ctx) const {
    cairo_save(ctx);
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_translate(ctx, location.x, location.y);
    cairo_rotate(ctx, rotation);

    cairo_rectangle(ctx, 0, 0, size.x, size.y);

    if (fill) {
        cairo_fill(ctx);
    }

    cairo_stroke(ctx);
    cairo_restore(ctx);
}
