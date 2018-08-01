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

void camera::encode_frame(scene &s) {
    capture(s);

    for (const auto& e : encoders) {
        e->encode(image.get());
    }
}

void camera::clear_encoders() {
    encoders.clear();
}

camera::camera(vec loc, vec camera_size)
    : location(-loc), size(camera_size),
      image(cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
      static_cast<int>(size.x), static_cast<int>(size.y)),
      cairo_surface_destroy),
      context(cairo_create(image.get()), cairo_destroy) {}
