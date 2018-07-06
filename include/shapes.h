#ifndef SHAPES_H
#define SHAPES_H

#include <cmath>
#include <memory>
#include <string>
#include <vector>

#include <cairo.h>

#include "vec.h"
#include "color.h"
#include "animators.h"

struct shape {
    color clr;
    std::vector<std::unique_ptr<animator>> animators;

    template <typename A, typename... Arg>
    void add_animator(Arg&&... args) {
        animators.emplace_back(std::make_unique<A>(std::forward<Arg>(args)...));
    }

    virtual void draw(cairo_t *) const = 0;
    void update(const int frame);

    shape() : shape({1.0, 1.0, 1.0, 1.0}) {}
    shape(color shape_clr) : clr(shape_clr) {}
    virtual ~shape() {}
};

struct ellipse : shape {
    vec location;
    vec size;
    vec angles;
    double rotation;
    bool fill;

    void draw(cairo_t *) const override;

    ellipse(vec loc, vec sz, double rotate, bool elp_fill) :
        location(loc), size(sz), angles({0.0, 2.0 * M_PI}),
        rotation(rotate), fill(elp_fill) {}

    ellipse(color elp_clr, vec loc, vec sz, double rotate, bool elp_fill) :
        shape(elp_clr), location(loc), size(sz), angles({0.0, 2.0 * M_PI}),
        rotation(rotate), fill(elp_fill) {}
};

struct arc : shape {
    vec location;
    vec size;
    vec angles;

    void draw(cairo_t *) const override;

    arc(vec loc, vec sz, vec arc_angles) :  location(loc), size(sz),
        angles(arc_angles) {}

    arc(color arc_clr, vec loc, vec sz, vec arc_angles) : shape(arc_clr),
        location(loc), size(sz), angles(arc_angles) {}
};

struct line : shape {
    vec start;
    vec end;

    void draw(cairo_t *) const override;

    line(vec line_start, vec line_end) : start(line_start), end(line_end) {}

    line(color line_clr, vec line_start, vec line_end) : shape(line_clr),
        start(line_start), end(line_end) {}
};

struct rectangle : shape {
    vec location;
    vec size;
    double rotation;
    bool fill;

    void draw(cairo_t *) const override;

    rectangle(vec loc, vec sz, double rotate, bool rec_fill) : location(loc),
        size(sz), rotation(rotate), fill(rec_fill) {}

    rectangle(color rec_clr, vec loc, vec sz, double rotate, bool rec_fill) :
        shape(rec_clr), location(loc), size(sz), rotation(rotate),
        fill(rec_fill) {}
};

struct text : shape {
    vec location;
    double size;
    double rotation;
    std::string str;
    std::string font;

    void draw(cairo_t *) const override;

    text(vec loc, double font_size, std::string string) :
        str(string), location(loc), size(font_size), rotation(0.0) {}

    text(vec loc, double font_size, std::string string, std::string str_font) :
        str(string), location(loc), size(font_size), rotation(0.0),
        font(str_font) {}

    text(color clr, vec loc, double font_size, std::string string,
         std::string str_font) : shape(clr), str(string), location(loc),
        size(font_size), rotation(0.0), font(str_font) {}
};

#endif //SHAPES_H
