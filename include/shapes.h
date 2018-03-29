#ifndef SHAPES_H
#define SHAPES_H

#include "vec.h"
#include "color.h"

struct scene;

void create_circle(scene &s, double radius, vec location, color clr);

void create_rectangle(scene &s, vec size, vec location, color clr);

#endif //SHAPES_H
