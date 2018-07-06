#include "../include/shapes.h"
#include "../include/scene.h"

void shape::update(const int frame) {
    for (auto& anim : animators) {
        anim->update(frame);
    }
}

void ellipse::draw(cairo_t *ctx) const {
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_rotate(ctx, rotation);

    if (size.x < size.y) {
        cairo_scale(ctx, size.x / size.y, 1.0);
        cairo_arc(ctx, location.x, location.y, size.y, angles.x, angles.y);
        cairo_scale(ctx, size.y / size.x, 1.0);
    } else if (size.x > size.y) {
        cairo_scale(ctx, 1.0, size.y / size.x);
        cairo_arc(ctx, location.x, location.y, size.x, angles.x, angles.y);
        cairo_scale(ctx, 1.0, size.x / size.y);
    } else if (size.x == size.y && size.x != 0) {
        cairo_arc(ctx, location.x, location.y, size.x, angles.x, angles.y);
    }

    if (fill) {
        cairo_fill(ctx);
    }

    cairo_stroke(ctx);
    cairo_rotate(ctx, -1.0 * rotation);
}

void arc::draw(cairo_t *ctx) const {
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);

    if (size.x < size.y) {
        cairo_scale(ctx, size.x / size.y, 1.0);
        cairo_arc(ctx, location.x, location.y, size.y, angles.x, angles.y);
        cairo_scale(ctx, size.y / size.x, 1.0);
    } else if (size.x > size.y) {
        cairo_scale(ctx, 1.0, size.y / size.x);
        cairo_arc(ctx, location.x, location.y, size.x, angles.x, angles.y);
        cairo_scale(ctx, 1.0, size.x / size.y);
    } else if (size.x == size.y && size.x != 0) {
        cairo_arc(ctx, location.x, location.y, size.x, angles.x, angles.y);
    }

    cairo_stroke(ctx);
}

void line::draw(cairo_t * ctx) const {
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_move_to(ctx, start.x, start.y);
    cairo_line_to(ctx, end.x, end.y);
    cairo_stroke(ctx);
}

void rectangle::draw(cairo_t *ctx) const {
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_rotate(ctx, rotation);

    cairo_rectangle(ctx, location.x, location.y, size.x, size.y);

    if (fill) {
        cairo_fill(ctx);
    }

    cairo_stroke(ctx);
    cairo_rotate(ctx, -1.0 * rotation);
}

void text::draw(cairo_t *ctx) const {
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_rotate(ctx, rotation);

    if (!font.empty()) {
        cairo_select_font_face(ctx, font.c_str(), CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_NORMAL);
    }

    cairo_set_font_size(ctx, size);

    cairo_move_to(ctx, location.x, location.y);
    cairo_show_text(ctx, str.c_str());

    cairo_stroke(ctx);
    cairo_rotate(ctx, -1.0 * rotation);
}
