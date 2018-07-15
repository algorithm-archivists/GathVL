#ifndef ARROW_H
#define ARROW_H

#include "object.h"
#include "../types/color.h"
#include "../types/vec.h"

struct arrow : object {
    color clr;
    vec location;
    double length;
    double rotation;

    void draw(cairo_t *) const override;

    arrow(vec location, double length, double rotation) :
        clr({1.0, 1.0, 1.0, 1.0}), location(location), length(fabs(length)),
        rotation(rotation) {}

    arrow(color clr, vec location, double length, double rotation) :
        clr(clr), location(location), length(fabs(length)),
        rotation(rotation) {}
};

#endif //ARROW_H
