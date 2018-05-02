#ifndef SHAPES_H
#define SHAPES_H

#include <cmath>
#include <cairo.h>
#include "vec.h"
#include "color.h"

enum shape_types {
    ELLIPSE,
    ARC,
    LINE,
    RECTANGLE
};

struct shape {
    shape_types type;
    color clr;

    shape(shape_types type0) : type(type0), clr({1.0, 1.0, 1.0, 1.0}) {}
    shape(shape_types type0, color clr0) : type(type0), clr(clr0) {}

    virtual void draw(cairo_t *) = 0;
};

struct ellipse : shape {
    vec location;
    vec size;
    vec angles;
    double rotation;
    bool fill;

    ellipse(vec location0, vec size0, double rotation0, bool fill0) :
            shape(ELLIPSE), location(location0), size(size0),
                rotation(rotation0), fill(fill0), angles({0.0, 2.0 * M_PI}) {}

    ellipse(color clr0, vec location0, vec size0, double rotation0, bool fill0)
            : shape(ELLIPSE, clr0), location(location0), size(size0),
                rotation(rotation0), fill(fill0), angles({0.0, 2.0 * M_PI}) {}

    void draw(cairo_t *);
};

struct arc : shape {
    vec location;
    vec size;
    vec angles;

    arc(vec location0, vec size0, vec angles0) : shape(ARC),
            location(location0), size(size0), angles(angles0) {}

    arc(color clr0, vec location0, vec size0, vec angles0) : shape(ARC, clr0),
            location(location0), size(size0), angles(angles0) {}

    void draw(cairo_t *);
};

struct line : shape {
    vec start;
    vec end;

    line(vec start0, vec end0) : shape(LINE), start(start0), end(end0) {}

    line(color clr0, vec start0, vec end0) : shape(LINE, clr0), start(start0),
            end(end0) {}

    void draw(cairo_t *);
};

struct rectangle : shape {
    vec location;
    vec size;
    double rotation;
    bool fill;

    rectangle(vec location0, vec size0, double rotation0, bool fill0) :
            shape(RECTANGLE), location(location0), size(size0),
            rotation(rotation0), fill(fill0) {}

    rectangle(color clr0, vec location0, vec size0, double rotation0,
            bool fill0) : shape(RECTANGLE, clr0), location(location0),
                size(size0), rotation(rotation0), fill(fill0) {}

    void draw(cairo_t *);
};

#endif //SHAPES_H
