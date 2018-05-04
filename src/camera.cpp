#include "../include/camera.h"
#include "../include/scene.h"

void camera::clear_camera() {
    cairo_set_source_rgba(context.get(), 0, 0, 0, 0);
    cairo_set_operator(context.get(), CAIRO_OPERATOR_SOURCE);
    cairo_paint(context.get());
}

void camera::move_by(vec displace) {
    location -= displace;
}

void camera::move_to(vec position) {
    location = position;
}

void camera::capture(scene &s) {
    s.draw();
    cairo_set_source_surface(context.get(), s.surface.get(),
                             static_cast<int>(location.x),
                             static_cast<int>(location.y));
    cairo_paint(context.get());
}

void camera::write_to_png(scene &s, const char *url) {
    capture(s);
    cairo_surface_write_to_png(image.get(), url);
}

camera::camera(vec loc, vec camera_size, std::string url)
    : location(-1 * loc), size(camera_size), url_base(url),
      image(cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
      static_cast<int>(size.x), static_cast<int>(size.y)),
      cairo_surface_destroy),
      context(cairo_create(image.get()), cairo_destroy) {}
