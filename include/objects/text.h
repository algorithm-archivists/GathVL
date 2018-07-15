#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "object.h"
#include "../types/color.h"
#include "../types/vec.h"

struct text : object {
    color clr;
    vec location;
    double size;
    double rotation;
    std::string str;
    std::string font;

    void draw(cairo_t *) const override;

    text(vec location, double size, const std::string& str) :
        clr({1.0, 1.0, 1.0, 1.0}), str(str), location(location),
        size(fabs(size)), rotation(0.0) {}

    text(vec location, double size, const std::string& str,
         const std::string& font) :
        clr({1.0, 1.0, 1.0, 1.0}), str(str), location(location),
        size(fabs(size)), rotation(0.0), font(font) {}

    text(color clr, vec location, double size, const std::string& str,
         double rotation) :
        clr(clr), str(str), location(location), size(fabs(size)),
        rotation(rotation) {}

    text(color clr, vec location, double size, const std::string& str,
         const std::string& font, double rotation) :
        clr(clr), str(str), location(location), size(fabs(size)),
        rotation(rotation), font(font) {}
};

#endif //TEXT_H
