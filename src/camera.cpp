#include "../include/camera.h"
#include "../include/scene.h"

#include <sstream>

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

void camera::write_to_png(scene &s, const int frame) {
    capture(s);

    std::string png_url;
    std::stringstream ss;
    ss << std::setw(5) << std::setfill('0') << frame;
    png_url = url + ss.str() + ".png";

    cairo_surface_write_to_png(image.get(), png_url.c_str());
}

camera::camera(vec loc, vec camera_size, std::string str)
    : location(-1 * loc), size(camera_size), url(str),
      image(cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
      static_cast<int>(size.x), static_cast<int>(size.y)),
      cairo_surface_destroy),
      context(cairo_create(image.get()), cairo_destroy) {}
