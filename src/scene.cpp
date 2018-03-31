#include "../include/scene.h"

void scene::draw(cairo_t *ctx) {
    for (auto s : shape_vector) {
        s.draw(ctx, s);
    }
}
