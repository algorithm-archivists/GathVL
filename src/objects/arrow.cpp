#include "../../include/objects/arrow.h"

void arrow::draw(cairo_t *ctx) const {
    cairo_save(ctx);
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_translate(ctx, location.x, location.y);
    cairo_rotate(ctx, rotation);

    cairo_move_to(ctx, 0, 0);
    cairo_line_to(ctx, length, 0);
    cairo_rotate(ctx, -M_PI / 4);
    cairo_move_to(ctx, 0, 0);
    cairo_line_to(ctx, 0.25 * length, 0);
    cairo_move_to(ctx, 0, 0);
    cairo_rotate(ctx, M_PI / 2);
    cairo_line_to(ctx, 0.25 * length, 0);

    cairo_stroke(ctx);
    cairo_restore(ctx);
}
