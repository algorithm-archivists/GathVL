#include "../../include/objects/text.h"

void text::draw(cairo_t *ctx) const {
    cairo_save(ctx);
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_translate(ctx, location.x, location.y);
    cairo_rotate(ctx, rotation);

    if (!font.empty()) {
        cairo_select_font_face(ctx, font.c_str(), CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_NORMAL);
    }

    cairo_set_font_size(ctx, size);

    cairo_move_to(ctx, 0, 0);
    cairo_show_text(ctx, str.c_str());

    cairo_stroke(ctx);
    cairo_restore(ctx);
}
