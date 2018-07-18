#ifndef GATHVL_CURVE_H
#define GATHVL_CURVE_H

#include "object.h"
#include "../types/color.h"
#include "../types/vec.h"

struct curve : object {
    color clr;
    vec origin;
    std::vector<vec> points;

    void draw(cairo_t *) const override;

    curve(const std::vector<vec>& points, vec origin) :
        clr({1.0, 1.0, 1.0, 1.0}), points(points), origin(origin) {}

    curve(color clr, const std::vector<vec>& points, vec origin) :
        clr(clr), points(points), origin(origin) {}
};

#endif //GATHVL_CURVE_H
