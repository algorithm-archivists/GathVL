#ifndef GATHVL_IMAGE_H
#define GATHVL_IMAGE_H

#include <memory>
#include <string>

#include <cairo.h>

#include "object.h"
#include "../types/vec.h"

struct image : object {
    vec location;
    double rotation;

    void draw(cairo_t*) const override;

    image(const std::string& url, vec location) :
        image(url, location, 0.0) {}

    image(const std::string& url, vec location, double rotation) :
        image(url, location, rotation, {0, 0}) {}

    image(const std::string& url, vec location, double rotation, vec size);

    ~image();

private:
    vec size;
    unsigned char *image_data;
    cairo_surface_t *surface;
};

#endif //GATHVL_IMAGE_H
