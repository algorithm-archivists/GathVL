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

    ellipse(vec loc, vec elp_size, double rotate, bool elp_fill) :
        location(loc), size(elp_size), angles({0.0, 2.0 * M_PI}),
        rotation(rotate), fill(elp_fill) {}

    ellipse(color clr, vec loc, vec elp_size, double rotate, bool elp_fill) :
        shape(clr), location(loc), size(elp_size), angles({0.0, 2.0 * M_PI}),
        rotation(rotate), fill(elp_fill) {}
};

struct arc : shape {
    vec location;
    vec size;
    vec angles;

    void draw(cairo_t *) const override;

    arc(vec loc, vec arc_size, vec arc_angles) :
        location(loc), size(arc_size), angles(arc_angles) {}

    arc(color clr, vec loc, vec arc_size, vec arc_angles) :
        shape(clr), location(loc), size(arc_size), angles(arc_angles) {}
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

    rectangle(vec loc, vec rec_size, double rotate, bool rec_fill) :
        location(loc), size(rec_size), rotation(rotate), fill(rec_fill) {}

    rectangle(color clr, vec loc, vec rec_size, double rotate, bool rec_fill) :
        shape(clr), location(loc), size(rec_size), rotation(rotate),
        fill(rec_fill) {}
};

struct text : shape {
    vec location;
    double size;
    double rotation;
    std::string str;
    std::string font;

    void draw(cairo_t *) const override;

    text(vec loc, double text_size, const std::string& text_str) :
        str(text_str), location(loc), size(text_size), rotation(0.0) {}

    text(vec loc, double text_size, const std::string& text_str,
         const std::string& text_font) :
        str(text_str), location(loc), size(text_size), rotation(0.0),
        font(text_font) {}

    text(color clr, vec loc, double font_size, const std::string& text_str,
         const std::string& text_font) :
        shape(clr), str(text_str), location(loc), size(font_size),
        rotation(0.0), font(text_font) {}
};

struct arrow : shape {
    vec location;
    double length;
    double rotation;

    void draw(cairo_t *) const override;

    arrow(vec loc, double len, double rotate) :
        location(loc), length(len), rotation(rotate) {}

    arrow(color clr, vec loc, double len, double rotate) :
        shape(clr), location(loc), length(len), rotation(rotate) {}
};

struct curve : shape {
    std::vector<vec> points;

    void draw(cairo_t *) const override;

    explicit curve(const std::vector<vec>& curve_points) :
        points(curve_points) {}

    explicit curve(color clr, const std::vector<vec>& curve_points) :
        shape(clr), points(curve_points) {}
};

struct polygon : shape {
    std::vector<vec> points;
    double rotation;
    bool fill;

    void draw(cairo_t *) const override;

    polygon(const std::vector<vec>& curve_points, bool fill_polygon) :
        points(curve_points), fill(fill_polygon), rotation(0) {}

    polygon(const std::vector<vec>& curve_points, bool fill_polygon,
            double rotate) :
        points(curve_points), fill(fill_polygon), rotation(rotate) {}

    polygon(color clr, const std::vector<vec>& curve_points, bool fill_polygon,
            double rotate) : shape(clr), points(curve_points),
        fill(fill_polygon), rotation(rotate) {}
};

#endif //SHAPES_H
