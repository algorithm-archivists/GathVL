#ifndef GATHVL_ELLIPSE_H
#define GATHVL_ELLIPSE_H

#include "object.h"
#include "../types/color.h"
#include "../types/vec.h"

struct ellipse : object {
    color clr;
    vec location;
    vec size;
    vec angles;
    double rotation;
    bool fill;

    void draw(cairo_t *) const override;

    ellipse(vec location, vec size, double rotation, bool fill) :
        clr({1.0, 1.0, 1.0, 1.0}), location(location),
        size({fabs(size.x), fabs(size.y)}), angles({0.0, 2.0 * M_PI}),
        rotation(rotation), fill(fill) {}

    ellipse(color clr, vec location, vec size, double rotation, bool fill) :
        clr(clr), location(location), size({fabs(size.x), fabs(size.y)}),
        angles({0.0, 2.0 * M_PI}), rotation(rotation), fill(fill) {}
};

#endif //GATHVL_ELLIPSE_H
