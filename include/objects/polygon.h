#ifndef GATHVL_POLYGON_H
#define GATHVL_POLYGON_H

#include <vector>

#include "object.h"
#include "../types/color.h"
#include "../types/vec.h"

struct polygon : object {
    color clr;
    vec center;
    std::vector<vec> points;
    double rotation;
    bool fill;

    void draw(cairo_t *) const override;

    polygon(const std::vector<vec>& points, bool fill) :
        clr({1.0, 1.0, 1.0, 1.0}), points(points), fill(fill), rotation(0),
        center({0.0, 0.0}) {}

    polygon(const std::vector<vec>& points, bool fill, double rotation,
            vec center) :
        clr({1.0, 1.0, 1.0, 1.0}), points(points), fill(fill),
        rotation(rotation), center(center) {}

    polygon(color clr, const std::vector<vec>& points, bool fill,
            double rotation, vec center) :
        clr(clr), points(points), fill(fill), rotation(rotation),
        center(center) {}
};

#endif //GATHVL_POLYGON_H
