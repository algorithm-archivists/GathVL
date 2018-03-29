#ifndef CAMERA_H
#define CAMERA_H

#include <cairo.h>
#include "vec.h"

struct scene;

struct camera {
    vec loc, size;
    cairo_surface_t *img;
    cairo_t *cam_ctx;

    void camera_init();

    camera() : loc({0, 0}), size({600, 400}) {
        camera_init();
    }

    camera(vec cam_size) : loc({0, 0}), size(cam_size) {
        camera_init();
    }

    camera(vec location, vec cam_size) : loc(-1 * location), size(cam_size) {
        camera_init();
    }

    ~camera() {
        cairo_destroy(cam_ctx);
        cairo_surface_destroy(img);
    }

    void clear();

    void move(vec displace);
    void move_to(vec location);

    void draw(scene &s);

    void write_to_png(scene &s, const char *url);

    void destroy();
};

#endif //CAMERA_H
