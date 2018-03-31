#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <vector>
#include "vec.h"
#include "color.h"

struct shape;

shape draw_ellipse(color ellipse_clr, vec location, vec size, double rotation,
                    int frame, vec interval);

#endif //ANIMATIONS_H
