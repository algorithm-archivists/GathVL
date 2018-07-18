#ifndef GATHVL_CAMERA_H
#define GATHVL_CAMERA_H

#include <memory>
#include <string>
#include <vector>

#include <cairo.h>

#include "encoders/encoder.h"
#include "encoders/png_encoder.h"
#include "encoders/video_encoder.h"
#include "types/vec.h"

struct scene;

struct camera {
    vec size;

    void clear_camera();

    void move_by(vec displace);
    void move_to(vec position);

    template <typename A, typename... Args>
    void add_encoder(Args&&... args) {
        using namespace std;
        encoders.emplace_back(make_unique<A>(forward<Args>(args)...));
    }

    void encode_frame(scene &s);
    void clear_encoders();

    camera() : camera({0, 0}, {600, 400}) {}
    camera(vec camera_size) : camera({0, 0}, camera_size) {}
    camera(vec loc, vec camera_size);

private:
    vec location;
    std::vector<std::unique_ptr<encoder>> encoders;
    std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> image;
    std::unique_ptr<cairo_t, decltype(&cairo_destroy)> context;

    void capture(scene &s);
};

#endif //GATHVL_CAMERA_H
