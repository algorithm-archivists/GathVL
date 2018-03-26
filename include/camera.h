#ifndef CAMERA_H
#define CAMERA_H

#include <cairo.h>
#include "vec.h"

struct scene;

struct camera {
    vec loc, size;
    cairo_surface_t *img;
    cairo_t *cam_ctx;

    camera() : loc({0, 0}), size({600, 400}) {}
    camera(vec cam_size) : loc({0, 0}), size(cam_size) {}
    camera(vec location, vec cam_size) : loc(-1 * location), size(cam_size) {}

    void clear();

    void move(vec displace);
    void move_to(vec location);

    void draw(scene *s);

    void write_to_png(scene *s, const char *url);

    void destroy();
};

#endif //CAMERA_H
