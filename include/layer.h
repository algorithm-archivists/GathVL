#ifndef GATHVL_LAYER_H
#define GATHVL_LAYER_H

#include <memory>
#include <vector>

#include <cairo.h>

#include "objects/arc.h"
#include "objects/arrow.h"
#include "objects/curve.h"
#include "objects/ellipse.h"
#include "objects/line.h"
#include "objects/object.h"
#include "objects/polygon.h"
#include "objects/rectangle.h"
#include "objects/text.h"
#include "types/color.h"
#include "types/vec.h"

struct layer {
    std::vector<std::shared_ptr<object>> objects;

    void draw(cairo_t *ctx) const;
    void update(int frame);

    void remove_object(int position);
    void clear();
};

#endif //GATHVL_LAYER_H
