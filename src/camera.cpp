#include "../include/camera.h"
#include "../include/scene.h"

void camera::clear() {
    cairo_set_source_rgba(cam_ctx, 0, 0, 0, 0);
    cairo_set_operator(cam_ctx, CAIRO_OPERATOR_SOURCE);
    cairo_paint(cam_ctx);
}

void camera::move(vec displace) {
    loc -= displace;
}

void camera::move_to(vec location) {
    loc = location;
}

void camera::draw(scene *s) {
    cairo_set_source_surface(cam_ctx, s->scene_surface, (int)loc.x, (int)loc.y);
    cairo_paint(cam_ctx);
}

void camera::write_to_png(scene *s, const char *url) {
    draw(s);

    cairo_surface_write_to_png(img, url);
    clear();
}

void camera::destroy(){
    cairo_destroy(cam_ctx);
    cairo_surface_destroy(img);
}
