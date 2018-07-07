#include "../include/shapes.h"
#include "../include/scene.h"

void shape::update(const int frame) {
    for (auto& anim : animators) {
        anim->update(frame);
    }
}

void ellipse::draw(cairo_t *ctx) const {
    cairo_save(ctx);
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_rotate(ctx, rotation);

    if (size.x < size.y) {
        cairo_scale(ctx, size.x / size.y, 1.0);
        cairo_arc(ctx, location.x, location.y, size.y, angles.x, angles.y);
    } else if (size.x > size.y) {
        cairo_scale(ctx, 1.0, size.y / size.x);
        cairo_arc(ctx, location.x, location.y, size.x, angles.x, angles.y);
    } else if (size.x == size.y && size.x != 0) {
        cairo_arc(ctx, location.x, location.y, size.x, angles.x, angles.y);
    }

    if (fill) {
        cairo_fill(ctx);
    }

    cairo_stroke(ctx);
    cairo_restore(ctx);
}

void arc::draw(cairo_t *ctx) const {
    cairo_save(ctx);
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);

    if (size.x < size.y) {
        cairo_scale(ctx, size.x / size.y, 1.0);
        cairo_arc(ctx, location.x, location.y, size.y, angles.x, angles.y);
    } else if (size.x > size.y) {
        cairo_scale(ctx, 1.0, size.y / size.x);
        cairo_arc(ctx, location.x, location.y, size.x, angles.x, angles.y);
    } else if (size.x == size.y && size.x != 0) {
        cairo_arc(ctx, location.x, location.y, size.x, angles.x, angles.y);
    }

    cairo_stroke(ctx);
    cairo_restore(ctx);
}

void line::draw(cairo_t * ctx) const {
    cairo_save(ctx);
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_move_to(ctx, start.x, start.y);
    cairo_line_to(ctx, end.x, end.y);
    cairo_stroke(ctx);
    cairo_restore(ctx);
}

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

void arrow::draw(cairo_t *ctx) const {
    cairo_save(ctx);
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_translate(ctx, location.x, location.y);
    cairo_rotate(ctx, rotation);

    cairo_move_to(ctx, 0, 0);
    cairo_line_to(ctx, -1.0 * length, 0);
    cairo_rotate(ctx, M_PI / 4);
    cairo_move_to(ctx, 0, 0);
    cairo_line_to(ctx, length * -0.2, 0);
    cairo_rotate(ctx, - M_PI / 2);
    cairo_move_to(ctx, 0, 0);
    cairo_line_to(ctx, length * -0.2, 0);
    cairo_rotate(ctx, M_PI / 4);

    cairo_stroke(ctx);
    cairo_restore(ctx);
}

void curve::draw(cairo_t *ctx) const {
    cairo_save(ctx);
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);

    if (!points.empty()) {
        cairo_move_to(ctx, points[0].x, points[0].y);
    }

    for (const auto& point : points) {
        cairo_line_to(ctx, point.x, point.y);
        cairo_move_to(ctx, point.x, point.y);
    }

    cairo_stroke(ctx);
    cairo_restore(ctx);
}

void polygon::draw(cairo_t *ctx) const {
    cairo_save(ctx);
    cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
    cairo_translate(ctx, points[0].x, points[0].y);
    cairo_rotate(ctx, rotation);

    for (const auto& point : points) {
        cairo_line_to(ctx, point.x - points[0].x, point.y - points[0].y);
        cairo_move_to(ctx, point.x - points[0].x, point.y - points[0].y);
    }

    cairo_line_to(ctx, 0, 0);

    if (fill) {
        cairo_fill(ctx);
    }

    cairo_stroke(ctx);
    cairo_restore(ctx);
}
