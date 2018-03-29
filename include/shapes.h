#ifndef SHAPES_H
#define SHAPES_H

#include <cairo.h>
#include "vec.h"
#include "color.h"

struct scene;

enum shape_types {
    ELLIPSE,
    RECTANGLE
};

struct shape {
    shape_types type;
    color clr;
    vec location;
    vec size;
    double angle;
    void (*handler)(cairo_t *, shape &);
};

void ellipse(shape &shp, color ellipse_clr, vec location, vec size,
                double angle);

void rectangle(shape &shp, color rec_clr, vec location, vec size, double angle);

void create_circle(scene &s, double radius, vec location, color clr);

void create_rectangle(scene &s, vec size, vec location, color clr);

#endif //SHAPES_H
