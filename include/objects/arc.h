#ifndef ARC_H
#define ARC_H

#include "object.h"
#include "../types/color.h"
#include "../types/vec.h"

struct arc : object {
    color clr;
    vec location;
    vec size;
    vec angles;

    void draw(cairo_t *) const override;

    arc(vec location, vec size, vec angles) :
        clr({1.0, 1.0, 1.0, 1.0}), location(location),
        size({fabs(size.x), fabs(size.y)}), angles(angles) {}

    arc(color clr, vec location, vec size, vec angles) :
        clr(clr), location(location), size({fabs(size.x), fabs(size.y)}),
        angles(angles) {}
};

#endif //ARC_H
