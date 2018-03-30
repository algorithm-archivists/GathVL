#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <vector>
#include "vec.h"
#include "color.h"

struct shape;

std::vector<shape> create_ellipse(color ellipse_clr, vec location, vec size,
                                    double rotation, int frames);

#endif //ANIMATIONS_H
