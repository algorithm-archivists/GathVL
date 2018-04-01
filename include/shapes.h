#ifndef SHAPES_H
#define SHAPES_H

#include <cairo.h>
#include "vec.h"
#include "color.h"

enum shape_types {
    ELLIPSE,
    ARC,
    LINE,
    RECTANGLE
};

struct extra {
    vec a;
};

struct shape {
    shape_types type;
    color clr;
    vec loc;
    vec size;
    double rotation;
    bool fill;
    extra ex;
    void (*draw)(cairo_t *, shape *s);
};

shape ellipse(color ellipse_clr, vec location, vec size, double rotation,
                bool fill);

shape arc(color arc_clr, vec location, vec size, vec angles);

shape line(color line_clr, vec start, vec end);

shape rectangle(color rec_clr, vec location, vec size, double rotation,
                bool fill);

#endif //SHAPES_H
