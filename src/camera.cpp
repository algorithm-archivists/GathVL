#include "../include/camera.h"
#include "../include/scene.h"

void camera::create_surfaces(scene &s) {
    img = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, size.x, size.y);
    cam_ctx = cairo_create(img);

    scene_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, s.size.x,
                                                s.size.y);
    scene_ctx = cairo_create(scene_surface);
    cairo_set_line_width(scene_ctx, 3);
    cairo_set_font_size(scene_ctx, 50.0);
    cairo_set_line_join(scene_ctx, CAIRO_LINE_JOIN_BEVEL);
    cairo_set_line_cap(scene_ctx, CAIRO_LINE_CAP_ROUND);

    cairo_set_source_rgba(scene_ctx, s.bg_clr.r, s.bg_clr.g, s.bg_clr.b,
                            s.bg_clr.a);
    cairo_rectangle(scene_ctx, 0, 0, s.size.x, s.size.y);
    cairo_fill(scene_ctx);
}

void camera::clear_camera() {
        cairo_set_source_rgba(cam_ctx, 0, 0, 0, 0);
        cairo_set_operator(cam_ctx, CAIRO_OPERATOR_SOURCE);
        cairo_paint(cam_ctx);
}

void camera::clear_scene(scene &s) {
    cairo_set_source_rgba(scene_ctx, s.bg_clr.r, s.bg_clr.g, s.bg_clr.b,
                            s.bg_clr.a);
    cairo_set_operator(scene_ctx, CAIRO_OPERATOR_SOURCE);
    cairo_paint(scene_ctx);
}

void camera::move(vec displace) {
    loc -= displace;
}

void camera::move_to(vec location) {
    loc = location;
}

void camera::draw(scene &s) {
    create_surfaces(s);
    s.draw(scene_ctx);
    cairo_set_source_surface(cam_ctx, scene_surface, (int)loc.x, (int)loc.y);
    cairo_paint(cam_ctx);
}

void camera::write_to_png(scene &s, const char *url) {
    draw(s);
    cairo_surface_write_to_png(img, url);
    destroy();
}

void camera::destroy() {
    cairo_destroy(cam_ctx);
    cairo_destroy(scene_ctx);
    cairo_surface_destroy(img);
    cairo_surface_destroy(scene_surface);
}
