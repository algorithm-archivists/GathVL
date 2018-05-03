#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include <cmath>
#include <cairo.h>
#include "vec.h"
#include "color.h"
#include "animators.h"

struct shape {
    color clr;
    std::vector<animator*> animators;

    virtual void draw(cairo_t *) = 0;
    void update(const int frame);
    void clear_animators();

    shape() : clr({1.0, 1.0, 1.0, 1.0}) {}
    shape(color shape_clr) : clr(shape_clr) {}
};

struct ellipse : shape {
    vec location;
    vec size;
    vec angles;
    double rotation;
    bool fill;

    void draw(cairo_t *) override;

    ellipse(vec loc, vec sz, double rotate, bool elp_fill) :
        location(loc), size(sz), rotation(rotate), fill(elp_fill),
        angles({0.0, 2.0 * M_PI}) {}

    ellipse(color elp_clr, vec loc, vec sz, double rotate, bool elp_fill) :
        shape(elp_clr), location(loc), size(sz), rotation(rotate),
        fill(elp_fill), angles({0.0, 2.0 * M_PI}) {}
};

struct arc : shape {
    vec location;
    vec size;
    vec angles;

    void draw(cairo_t *) override;

    arc(vec loc, vec sz, vec arc_angles) :  location(loc), size(sz),
        angles(arc_angles) {}

    arc(color arc_clr, vec loc, vec sz, vec arc_angles) : shape(arc_clr),
        location(loc), size(sz), angles(arc_angles) {}
};

struct line : shape {
    vec start;
    vec end;

    void draw(cairo_t *) override;

    line(vec line_start, vec line_end) : start(line_start), end(line_end) {}

    line(color line_clr, vec line_start, vec line_end) : shape(line_clr),
        start(line_start), end(line_end) {}
};

struct rectangle : shape {
    vec location;
    vec size;
    double rotation;
    bool fill;

    void draw(cairo_t *) override;

    rectangle(vec loc, vec sz, double rotate, bool rec_fill) : location(loc),
        size(sz), rotation(rotate), fill(rec_fill) {}

    rectangle(color rec_clr, vec loc, vec sz, double rotate, bool rec_fill) :
        shape(rec_clr), location(loc), size(sz), rotation(rotate),
        fill(rec_fill) {}
};

#endif //SHAPES_H
