#ifndef GATHVL_RECTANGLE_H
#define GATHVL_RECTANGLE_H

#include "object.h"
#include "../types/color.h"
#include "../types/vec.h"

struct rectangle : object {
    color clr;
    vec location;
    vec size;
    double rotation;
    bool fill;

    void draw(cairo_t *) const override;

    rectangle(vec location, vec size, double rotation, bool fill) :
        clr({1.0, 1.0, 1.0, 1.0}), location(location),
        size({fabs(size.x), fabs(size.y)}), rotation(rotation), fill(fill) {}

    rectangle(color clr, vec location, vec size, double rotation, bool fill) :
        clr(clr), location(location), size({fabs(size.x), fabs(size.y)}),
        rotation(rotation), fill(fill) {}
};

#endif //GATHVL_RECTANGLE_H
