#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <cairo.h>
#include "vec.h"

struct scene;

struct camera {
    vec location, size;
    std::string url_base;
    cairo_surface_t *image, *scene_surface;
    cairo_t *camera_ctx, *scene_ctx;

    void clear_camera();
    void clear_scene(scene &s);

    void move_by(vec displace);
    void move_to(vec position);

    void capture(scene &s);

    void write_to_png(scene &s, const char *url);

    void destroy();

    camera() : location({0, 0}), size({600, 400}), url_base("/tmp/img") {}

    camera(std::string url) : location({0, 0}), size({600, 400}),
        url_base(url) {}

    camera(vec camera_size, std::string url) : location({0, 0}),
        size(camera_size), url_base(url) {}

    camera(vec loc, vec camera_size, std::string url) : location(-1 * location),
        size(camera_size), url_base(url) {}

private:
    void create_surfaces(scene &s);
};

#endif //CAMERA_H
