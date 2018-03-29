#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <vector>
#include "vec.h"
#include "color.h"

struct scene;

void create_ellipse(std::vector<scene*> s_vec, color ellipse_clr, vec location,
                        vec size, double angle);

#endif //ANIMATIONS_H
