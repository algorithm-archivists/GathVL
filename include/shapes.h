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

    ellipse(vec location, vec size, double rotation, bool fill) :
        location(location), size(size), angles({0.0, 2.0 * M_PI}),
        rotation(rotation), fill(fill) {}

    ellipse(color clr, vec location, vec size, double rotation, bool fill) :
        shape(clr), location(location), size(size), angles({0.0, 2.0 * M_PI}),
        rotation(rotation), fill(fill) {}
};

struct arc : shape {
    vec location;
    vec size;
    vec angles;

    void draw(cairo_t *) const override;

    arc(vec location, vec size, vec angles) :
        location(location), size(size), angles(angles) {}

    arc(color clr, vec location, vec size, vec angles) :
        shape(clr), location(location), size(size), angles(angles) {}
};

struct line : shape {
    vec start;
    vec end;

    void draw(cairo_t *) const override;

    line(vec line_start, vec line_end) : start(line_start), end(line_end) {}

    line(color clr, vec line_start, vec line_end) :
        shape(clr), start(line_start), end(line_end) {}
};

struct rectangle : shape {
    vec location;
    vec size;
    double rotation;
    bool fill;

    void draw(cairo_t *) const override;

    rectangle(vec location, vec size, double rotation, bool fill) :
        location(location), size(size), rotation(rotation), fill(fill) {}

    rectangle(color clr, vec location, vec size, double rotation, bool fill) :
        shape(clr), location(location), size(size), rotation(rotation),
        fill(fill) {}
};

struct text : shape {
    vec location;
    double size;
    double rotation;
    std::string str;
    std::string font;

    void draw(cairo_t *) const override;

    text(vec location, double size, const std::string& str) :
        str(str), location(location), size(size), rotation(0.0) {}

    text(vec location, double size, const std::string& str,
         const std::string& font) :
        str(str), location(location), size(size), rotation(0.0), font(font) {}

    text(color clr, vec location, double size, cosnt std::string& str,
         double rotation) :
        shape(clr), str(str), location(location), size(size),
        rotation(rotation) {}

    text(color clr, vec location, double size, const std::string& str,
         const std::string& font, double rotation) :
        shape(clr), str(str), location(location), size(size),
        rotation(rotation), font(font) {}
};

struct arrow : shape {
    vec location;
    double length;
    double rotation;

    void draw(cairo_t *) const override;

    arrow(vec location, double length, double rotation) :
        location(location), length(length), rotation(rotation) {}

    arrow(color clr, vec location, double length, double rotation) :
        shape(clr), location(location), length(length), rotation(rotation) {}
};

struct curve : shape {
    std::vector<vec> points;

    void draw(cairo_t *) const override;

    explicit curve(const std::vector<vec>& curve_points) :
        points(curve_points) {}

    curve(color clr, const std::vector<vec>& curve_points) :
        shape(clr), points(curve_points) {}
};

struct polygon : shape {
    std::vector<vec> points;
    double rotation;
    bool fill;

    void draw(cairo_t *) const override;

    polygon(const std::vector<vec>& curve_points, bool fill) :
        points(curve_points), fill(fill), rotation(0) {}

    polygon(const std::vector<vec>& curve_points, bool fill, double rotation) :
        points(curve_points), fill(fill), rotation(rotation) {}

    polygon(color clr, const std::vector<vec>& curve_points, bool fill,
            double rotation) :
        shape(clr), points(curve_points), fill(fill), rotation(rotation) {}
};

#endif //SHAPES_H
