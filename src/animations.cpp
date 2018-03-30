#include "../include/animations.h"
#include "../include/shapes.h"

std::vector<shape> create_ellipse(color ellipse_clr, vec location, vec size,
                                    double rotation, int frames) {
    std::vector<shape> shp_vec;

    for (int i = 0; i < frames - 1; ++i) {
        shape shp = arc(ellipse_clr, location, size,
                            {0, i * 2.0 * M_PI / frames}, rotation);

        shp_vec.push_back(shp);
    }

    shape shp = ellipse(ellipse_clr, location, size, rotation);

    shp_vec.push_back(shp);

    return shp_vec;
}
