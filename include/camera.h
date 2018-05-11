#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include <string>

#include <cairo.h>

#include "camera_module.h"
#include "png_module.h"
#include "video_module.h"
#include "vec.h"

struct scene;

enum camera_modes {
    NONE,
    VIDEO,
    PNG
};

struct camera {
    void clear_camera();

    void move_by(vec displace);
    void move_to(vec position);

    void capture(scene &s);

    void open_module(camera_modes mode, std::string url);
    void encode_frame(scene &s);
    void close_module();

    camera() : camera(25) {}
    camera(int frames_per_sec) : camera({600, 400}, frames_per_sec) {}
    camera(vec camera_size, int frames_per_sec)
        : camera({0, 0}, camera_size, frames_per_sec) {}
    camera(vec loc, vec camera_size, int frames_per_sec);

private:
    vec location, size;
    int frame_rate;
    enum camera_modes mode;
    std::unique_ptr<camera_module> module;
    std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> image;
    std::unique_ptr<cairo_t, decltype(&cairo_destroy)> context;

};

#endif //CAMERA_H
