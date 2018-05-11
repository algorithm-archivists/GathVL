#ifndef CAMERA_MODULE_H
#define CAMERA_MODULE_H

#include <string>

#include <cairo.h>

struct camera_module {
    std::string url;

    virtual void encode(cairo_surface_t *image) = 0;

    camera_module(std::string file_location) : url(file_location) {}
    virtual ~camera_module() {}

};

#endif //CAMERA_MODULE_H
