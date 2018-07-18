#include "../../include/objects/line.h"

void line::draw(cairo_t * ctx) const {
    cairo_save(ctx);
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);

    cairo_move_to(ctx, start.x, start.y);
    cairo_line_to(ctx, end.x, end.y);

    cairo_stroke(ctx);
    cairo_restore(ctx);
}
