#include "../include/animations.h"
#include "../include/shapes.h"

shape draw_ellipse(color ellipse_clr, vec location, vec size, double rotation,
                    int frame, vec interval) {
    shape shp;

    if (frame > interval.x || frame < interval.y - 1) {
        shp = arc(ellipse_clr, location, size, {0, (frame - interval.x) * 2.0
                    * M_PI / (interval.y - interval.x)}, rotation);
    } else if (frame == interval.y) {
        shp = ellipse(ellipse_clr, location, size, rotation);
    }

    return shp;
}
