#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <cairo.h>
#include "vec.h"

struct scene;

struct camera {
    vec loc, size;
    std::string url_base;
    cairo_surface_t *img, *scene_surface;
    cairo_t *cam_ctx, *scene_ctx;

    void create_surfaces(scene &s);

    void clear_camera();
    void clear_scene(scene &s);

    void move(vec displace);
    void move_to(vec location);

    void draw(scene &s);

    void write_to_png(scene &s, const char *url);

    void destroy();

    camera() : loc({0, 0}), size({600, 400}), url_base("/tmp/img") {}

    camera(std::string url) : loc({0, 0}), size({600, 400}), url_base(url) {}

    camera(vec cam_size, std::string url) :
            loc({0, 0}), size(cam_size), url_base(url) {}

    camera(vec location, vec cam_size, std::string url) :
            loc(-1 * location), size(cam_size) {}
};

#endif //CAMERA_H
