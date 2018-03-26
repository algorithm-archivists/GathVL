#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <cairo.h>
#include "vec.h"
#include "color.h"

struct scene {
    vec size;
    cairo_surface_t *scene_surface;
    cairo_t *scene_ctx;
    std::string url_base;
    color bg_clr;

    void scene_init();

    scene(std::string url) :
        size({600, 400}), url_base(url), bg_clr({0.0, 0.0, 0.0, 1.0}) {
        scene_init();
    }

    scene(std::string url, color bg_color) :
        size({600, 400}), url_base(url), bg_clr(bg_color) {
        scene_init();
    }

    scene(vec scene_size, std::string url) :
        size(scene_size), url_base(url), bg_clr({0.0, 0.0, 0.0, 1.0}) {
        scene_init();
    }

    scene(vec scene_size, std::string url, color bg_color) :
        size(scene_size), url_base(url), bg_clr(bg_color) {
        scene_init();
    }

    void clear();

    void destroy();
};

#endif //SCENE_H
