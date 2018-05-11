#ifndef PNG_MODULE_H
#define PNG_MODULE_H

#include <string>

#include <cairo.h>

#include "camera_module.h"

struct png_module : camera_module {
    int count;

    void encode(cairo_surface_t *image) override;

    png_module() : png_module("/tmp/img") {}
    png_module(std::string url);
};

#endif //PNG_MODULE_H
