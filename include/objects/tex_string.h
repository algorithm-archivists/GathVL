#ifndef GATHVL_TEX_STRING_H
#define GATHVL_TEX_STRING_H

#include <string>

#include <cairo.h>

#include "object.h"
#include "../types/color.h"
#include "../types/vec.h"

struct tex_string : object {
    color clr;
    vec location;
    vec size;
    double rotation;

    void draw(cairo_t*) const override;

    tex_string(const std::string& str, vec location) :
        tex_string(str, location, {0, 0}) {}

    tex_string(const std::string& str, vec location, vec size) :
        tex_string(str, location, size, 0.0, {1, 1, 1, 1}) {}

    tex_string(const std::string& str, vec location, vec size, double rotation,
               color clr);

    ~tex_string();

private:
    std::string texfile;
    unsigned char *image_data;
    int width;
    int height;
};

#endif //GATHVL_TEX_STRING_H
