#ifndef GATHVL_PNG_ENCODER_H
#define GATHVL_PNG_ENCODER_H

#include <string>

#include <cairo.h>

#include "encoder.h"

struct png_encoder : encoder {
    int count;

    void encode(cairo_surface_t *image) override;

    png_encoder() : png_encoder("/tmp/img") {}
    png_encoder(std::string url);
};

#endif //GATHVL_PNG_ENCODER_H
