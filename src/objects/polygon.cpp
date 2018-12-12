#include "../../include/objects/polygon.h"

void polygon::draw(cairo_t *ctx) const {
    cairo_save(ctx);
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_translate(ctx, center.x, center.y);
    cairo_rotate(ctx, rotation);

    if (!points.empty()) {
        cairo_move_to(ctx, points.back().x - center.x,
                      points.back().y - center.y);
    }

    for (const auto& point : points) {
        cairo_line_to(ctx, point.x - center.x, point.y - center.y);
    }

    cairo_close_path(ctx);
    if (fill) {
        cairo_fill(ctx);
    }

    cairo_stroke(ctx);
    cairo_restore(ctx);
}
