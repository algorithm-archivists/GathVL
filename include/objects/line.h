#ifndef GATHVL_LINE_H
#define GATHVL_LINE_H

#include "object.h"
#include "../types/color.h"
#include "../types/vec.h"

struct line : object {
    color clr;
    vec start;
    vec end;

    void draw(cairo_t *) const override;

    line(vec line_start, vec line_end) :
        clr({1.0, 1.0, 1.0, 1.0}), start(line_start), end(line_end) {}

    line(color clr, vec line_start, vec line_end) :
        clr(clr), start(line_start), end(line_end) {}
};

#endif //GATHVL_LINE_H
