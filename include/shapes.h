#ifndef SHAPES_H
#define SHAPES_H

#include <cairo.h>
#include "vec.h"
#include "color.h"

enum shape_types {
    ELLIPSE,
    RECTANGLE,
    ARC
};

struct extra {
    double arc_start_angle,
            arc_end_angle;
};

struct shape {
    shape_types type;
    color clr;
    vec location;
    vec size;
    double rotation;
    struct extra;
    void (*draw)(cairo_t *, shape &s);
};

shape ellipse(color ellipse_clr, vec location, vec size, double rotation);

shape rectangle(color rec_clr, vec location, vec size, double rotation);

shape arc(color arc_clr, vec location, vec size, double start_angle,
            double end_angle, double rotation);

#endif //SHAPES_H
