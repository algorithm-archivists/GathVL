#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include <string>

#include <cairo.h>

#include "vec.h"

struct scene;

struct camera {
    vec location, size;
    std::string url;

    std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> image;
    std::unique_ptr<cairo_t, decltype(&cairo_destroy)> context;

    void clear_camera();

    void move_by(vec displace);
    void move_to(vec position);

    void capture(scene &s);
    void write_to_png(scene &s, const char *url);

    camera() : camera("/tmp/img") {}
    camera(std::string str) : camera({600, 400}, str) {}
    camera(vec camera_size, std::string str)
        : camera({0, 0}, camera_size, str) {}
    camera(vec loc, vec camera_size, std::string str);
};

#endif //CAMERA_H
