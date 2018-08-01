#include "../../include/objects/curve.h"

void curve::draw(cairo_t *ctx) const {
    cairo_save(ctx);
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_translate(ctx, origin.x, origin.y);

    if (!points.empty()) {
        cairo_move_to(ctx, points[0].x, -points[0].y);
    }

    for (const auto& point : points) {
        cairo_line_to(ctx, point.x, -point.y);
        cairo_move_to(ctx, point.x, -point.y);
    }

    cairo_stroke(ctx);
    cairo_restore(ctx);
}
