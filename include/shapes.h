#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include <cmath>
#include <cairo.h>
#include "vec.h"
#include "color.h"
#include "animators.h"

enum shape_type {
    ELLIPSE,
    ARC,
    LINE,
    RECTANGLE
};

struct shape {
    shape_type type;
    color clr;
    std::vector<animator*> animators;

    virtual void draw(cairo_t *) = 0;
    void update(int frame);
    void clear_animators();

    shape(shape_type type0) : type(type0), clr({1.0, 1.0, 1.0, 1.0}) {}
    shape(shape_type type0, color clr0) : type(type0), clr(clr0) {}
};

struct ellipse : shape {
    vec location;
    vec size;
    vec angles;
    double rotation;
    bool fill;

    void draw(cairo_t *);

    ellipse(vec location0, vec size0, double rotation0, bool fill0) :
            shape(ELLIPSE), location(location0), size(size0),
                rotation(rotation0), fill(fill0), angles({0.0, 2.0 * M_PI}) {}

    ellipse(color clr0, vec location0, vec size0, double rotation0, bool fill0)
            : shape(ELLIPSE, clr0), location(location0), size(size0),
                rotation(rotation0), fill(fill0), angles({0.0, 2.0 * M_PI}) {}

    ellipse(ellipse *e) : shape(ELLIPSE, e->clr), location(e->location),
            size(e->size), rotation(e->rotation), fill(e->fill),
            angles(e->angles) {}

};

struct arc : shape {
    vec location;
    vec size;
    vec angles;

    void draw(cairo_t *);

    arc(vec location0, vec size0, vec angles0) : shape(ARC),
            location(location0), size(size0), angles(angles0) {}

    arc(color clr0, vec location0, vec size0, vec angles0) : shape(ARC, clr0),
            location(location0), size(size0), angles(angles0) {}

    arc(arc *a) : shape(ARC, a->clr), location(a->location), size(a->size),
            angles(a->angles) {}
};

struct line : shape {
    vec start;
    vec end;

    void draw(cairo_t *);

    line(vec start0, vec end0) : shape(LINE), start(start0), end(end0) {}

    line(color clr0, vec start0, vec end0) : shape(LINE, clr0), start(start0),
            end(end0) {}

    line(line *l) : shape(LINE, l->clr), start(l->start), end(l->end) {}
};

struct rectangle : shape {
    vec location;
    vec size;
    double rotation;
    bool fill;

    void draw(cairo_t *);

    rectangle(vec location0, vec size0, double rotation0, bool fill0) :
            shape(RECTANGLE), location(location0), size(size0),
            rotation(rotation0), fill(fill0) {}

    rectangle(color clr0, vec location0, vec size0, double rotation0,
            bool fill0) : shape(RECTANGLE, clr0), location(location0),
                size(size0), rotation(rotation0), fill(fill0) {}

    rectangle(rectangle *r) : shape(RECTANGLE, r->clr), location(r->location),
            size(r->size), rotation(r->rotation), fill(r->fill) {}
};

#endif //SHAPES_H
