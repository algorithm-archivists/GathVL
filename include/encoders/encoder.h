#ifndef ENCODER_H
#define ENCODER_H

#include <string>

#include <cairo.h>

struct encoder {
    virtual void encode(cairo_surface_t *image) = 0;

    encoder(std::string file_location) : url(file_location) {}
    virtual ~encoder() {}

protected:
    std::string url;
};

#endif //ENCODER_H
